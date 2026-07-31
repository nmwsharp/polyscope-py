#include "ImGuiFileDialog.h"

#include <nanobind/nanobind.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

using Vec2T = std::tuple<float, float>;

void bind_imgui_file_dialog(nb::module_& m) {
  // Configuration value passed to OpenDialog(). Pointer and callback fields are intentionally omitted.
  nb::class_<IGFD::FileDialogConfig>(m, "FileDialogConfig")
      .def(
          nb::new_([](const std::string& path, const std::string& file_name,
                      const std::string& file_path_name, int32_t count_selection_max,
                      ImGuiFileDialogFlags flags, float side_pane_width) {
            IGFD::FileDialogConfig config;
            config.path = path;
            config.fileName = file_name;
            config.filePathName = file_path_name;
            config.countSelectionMax = count_selection_max;
            config.flags = flags;
            config.sidePaneWidth = side_pane_width;
            return config;
          }),
          nb::kw_only(), nb::arg("path") = "", nb::arg("fileName") = "",
          nb::arg("filePathName") = "", nb::arg("countSelectionMax") = 1,
          nb::arg("flags") = static_cast<ImGuiFileDialogFlags>(ImGuiFileDialogFlags_None),
          nb::arg("sidePaneWidth") = 250.0f)
      .def_rw("path", &IGFD::FileDialogConfig::path)
      .def_rw("fileName", &IGFD::FileDialogConfig::fileName)
      .def_rw("filePathName", &IGFD::FileDialogConfig::filePathName)
      .def_rw("countSelectionMax", &IGFD::FileDialogConfig::countSelectionMax)
      .def_rw("flags", &IGFD::FileDialogConfig::flags)
      .def_rw("sidePaneWidth", &IGFD::FileDialogConfig::sidePaneWidth);

  // Ordinary API backed by FileDialog::Instance(), so callers do not need to retain a dialog object.
  m.def(
      "OpenDialog",
      [](const std::string& key, const std::string& title,
         const std::optional<std::string>& filters, const std::optional<IGFD::FileDialogConfig>& config) {
        IGFD::FileDialog::Instance()->OpenDialog(key, title, filters ? filters->c_str() : nullptr,
                                                 config.value_or(IGFD::FileDialogConfig{}));
      },
      nb::arg("key"), nb::arg("title"), nb::arg("filters").none(),
      nb::arg("config").none() = nb::none());
  m.def(
      "Display",
      [](const std::string& key, ImGuiWindowFlags flags, const Vec2T& min_size, const Vec2T& max_size) {
        return IGFD::FileDialog::Instance()->Display(
            key, flags, ImVec2(std::get<0>(min_size), std::get<1>(min_size)),
            ImVec2(std::get<0>(max_size), std::get<1>(max_size)));
      },
      nb::arg("key"), nb::arg("flags") = static_cast<ImGuiWindowFlags>(ImGuiWindowFlags_NoCollapse),
      nb::arg("min_size") = Vec2T{0.0f, 0.0f}, nb::arg("max_size") = Vec2T{FLT_MAX, FLT_MAX});
  m.def("Close", []() { IGFD::FileDialog::Instance()->Close(); });
  m.def(
      "IsOpened",
      [](const std::optional<std::string>& key) {
        return key ? IGFD::FileDialog::Instance()->IsOpened(*key) : IGFD::FileDialog::Instance()->IsOpened();
      },
      nb::arg("key").none() = nb::none());
  m.def("GetOpenedKey", []() { return IGFD::FileDialog::Instance()->GetOpenedKey(); });
  m.def("IsOk", []() { return IGFD::FileDialog::Instance()->IsOk(); });
  m.def(
      "GetSelection",
      [](IGFD_ResultMode mode) {
        nb::dict selection;
        for (const auto& [filename, path] : IGFD::FileDialog::Instance()->GetSelection(mode)) {
          selection[nb::str(filename.c_str())] = nb::str(path.c_str());
        }
        return selection;
      },
      nb::arg("mode") = static_cast<IGFD_ResultMode>(IGFD_ResultMode_KeepInputFile));
  m.def("GetFilePathName", [](IGFD_ResultMode mode) {
    return IGFD::FileDialog::Instance()->GetFilePathName(mode);
  }, nb::arg("mode") = static_cast<IGFD_ResultMode>(IGFD_ResultMode_AddIfNoFileExt));
  m.def("GetCurrentFileName", [](IGFD_ResultMode mode) {
    return IGFD::FileDialog::Instance()->GetCurrentFileName(mode);
  }, nb::arg("mode") = static_cast<IGFD_ResultMode>(IGFD_ResultMode_AddIfNoFileExt));
  m.def("GetCurrentPath", []() { return IGFD::FileDialog::Instance()->GetCurrentPath(); });
  m.def("GetCurrentFilter", []() { return IGFD::FileDialog::Instance()->GetCurrentFilter(); });

  // Advanced API for independently owned dialogs, plus access to the upstream library-owned singleton.
  auto file_dialog_class = nb::class_<IGFD::FileDialog>(m, "FileDialog");
  file_dialog_class
      .def(nb::init<>())
      .def_static("Instance", []() { return IGFD::FileDialog::Instance(); }, nb::rv_policy::reference)
      .def(
          "OpenDialog",
          [](IGFD::FileDialog& dialog, const std::string& key, const std::string& title,
             const std::optional<std::string>& filters, const std::optional<IGFD::FileDialogConfig>& config) {
            dialog.OpenDialog(key, title, filters ? filters->c_str() : nullptr,
                              config.value_or(IGFD::FileDialogConfig{}));
          },
          nb::arg("key"), nb::arg("title"), nb::arg("filters").none(),
          nb::arg("config").none() = nb::none())
      .def(
          "Display",
          [](IGFD::FileDialog& dialog, const std::string& key, ImGuiWindowFlags flags,
             const Vec2T& min_size, const Vec2T& max_size) {
            return dialog.Display(key, flags, ImVec2(std::get<0>(min_size), std::get<1>(min_size)),
                                  ImVec2(std::get<0>(max_size), std::get<1>(max_size)));
          },
          nb::arg("key"), nb::arg("flags") = static_cast<ImGuiWindowFlags>(ImGuiWindowFlags_NoCollapse),
          nb::arg("min_size") = Vec2T{0.0f, 0.0f}, nb::arg("max_size") = Vec2T{FLT_MAX, FLT_MAX})
      .def("Close", &IGFD::FileDialog::Close)
      .def("IsOpened", nb::overload_cast<>(&IGFD::FileDialog::IsOpened, nb::const_))
      .def("IsOpened", nb::overload_cast<const std::string&>(&IGFD::FileDialog::IsOpened, nb::const_),
           nb::arg("key"))
      .def("GetOpenedKey", &IGFD::FileDialog::GetOpenedKey)
      .def("IsOk", &IGFD::FileDialog::IsOk)
      .def(
          "GetSelection",
          [](IGFD::FileDialog& dialog, IGFD_ResultMode mode) {
            nb::dict selection;
            for (const auto& [filename, path] : dialog.GetSelection(mode)) {
              selection[nb::str(filename.c_str())] = nb::str(path.c_str());
            }
            return selection;
          },
          nb::arg("mode") = static_cast<IGFD_ResultMode>(IGFD_ResultMode_KeepInputFile))
      .def("GetFilePathName", &IGFD::FileDialog::GetFilePathName,
           nb::arg("mode") = static_cast<IGFD_ResultMode>(IGFD_ResultMode_AddIfNoFileExt))
      .def("GetCurrentFileName", &IGFD::FileDialog::GetCurrentFileName,
           nb::arg("mode") = static_cast<IGFD_ResultMode>(IGFD_ResultMode_AddIfNoFileExt))
      .def("GetCurrentPath", &IGFD::FileDialog::GetCurrentPath)
      .def("GetCurrentFilter", &IGFD::FileDialog::GetCurrentFilter);

  // Export flags and result modes
#define BIND_IGFD_CONSTANT(name) m.attr(#name) = nb::int_(static_cast<int>(name))
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_None);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_ConfirmOverwrite);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_DontShowHiddenFiles);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_DisableCreateDirectoryButton);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_HideColumnType);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_HideColumnSize);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_HideColumnDate);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_NoDialog);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_ReadOnlyFileNameField);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_CaseInsensitiveExtentionFiltering);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_Modal);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_DisableThumbnailMode);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_DisablePlaceMode);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_DisableQuickPathSelection);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_ShowDevicesButton);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_NaturalSorting);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_OptionalFileName);
  BIND_IGFD_CONSTANT(ImGuiFileDialogFlags_Default);
  BIND_IGFD_CONSTANT(IGFD_ResultMode_AddIfNoFileExt);
  BIND_IGFD_CONSTANT(IGFD_ResultMode_OverwriteFileExt);
  BIND_IGFD_CONSTANT(IGFD_ResultMode_KeepInputFile);
#undef BIND_IGFD_CONSTANT
}
