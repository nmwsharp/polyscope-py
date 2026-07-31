#include "ImGuiFileDialog.h"

#include <nanobind/nanobind.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/tuple.h>

namespace nb = nanobind;
using namespace nb::literals;

using Vec2T = std::tuple<float, float>;

/// Resolve the sentinel default to half the viewport, since ImGuiFileDialog's default minimum size
/// allows the window to collapse 
ImVec2 resolve_min_size(const Vec2T& min_size) {
  if (std::get<0>(min_size) < 0.0f && std::get<1>(min_size) < 0.0f) {
    const ImVec2 viewport_size = ImGui::GetMainViewport()->Size;
    return ImVec2(viewport_size.x * 0.5f, viewport_size.y * 0.5f);
  }
  return ImVec2(std::get<0>(min_size), std::get<1>(min_size));
}

void bind_imgui_file_dialog(nb::module_& imgui_module) {
  auto m = imgui_module.def_submodule("file_dialog", "ImGuiFileDialog bindings");

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
        return IGFD::FileDialog::Instance()->Display(key, flags, resolve_min_size(min_size),
                                                     ImVec2(std::get<0>(max_size), std::get<1>(max_size)));
      },
      nb::arg("key"), nb::arg("flags") = static_cast<ImGuiWindowFlags>(ImGuiWindowFlags_NoCollapse),
      nb::arg("min_size") = Vec2T{-1.0f, -1.0f}, nb::arg("max_size") = Vec2T{FLT_MAX, FLT_MAX});
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
            return dialog.Display(key, flags, resolve_min_size(min_size),
                                  ImVec2(std::get<0>(max_size), std::get<1>(max_size)));
          },
          nb::arg("key"), nb::arg("flags") = static_cast<ImGuiWindowFlags>(ImGuiWindowFlags_NoCollapse),
          nb::arg("min_size") = Vec2T{-1.0f, -1.0f}, nb::arg("max_size") = Vec2T{FLT_MAX, FLT_MAX})
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

  {
    auto e = nb::enum_<ImGuiFileDialogFlags_>(m, "ImGuiFileDialogFlags_", nb::is_arithmetic(),
                                               nb::is_flag());
#define BIND_IGFD_ENUM_VALUE(name) \
  e.value(#name, name);             \
  m.attr(#name) = ImGuiFileDialogFlags_::name
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_None);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_ConfirmOverwrite);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_DontShowHiddenFiles);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_DisableCreateDirectoryButton);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_HideColumnType);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_HideColumnSize);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_HideColumnDate);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_NoDialog);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_ReadOnlyFileNameField);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_CaseInsensitiveExtentionFiltering);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_Modal);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_DisableThumbnailMode);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_DisablePlaceMode);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_DisableQuickPathSelection);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_ShowDevicesButton);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_NaturalSorting);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_OptionalFileName);
    BIND_IGFD_ENUM_VALUE(ImGuiFileDialogFlags_Default);
#undef BIND_IGFD_ENUM_VALUE
  }

  {
    auto e = nb::enum_<IGFD_ResultMode_>(m, "IGFD_ResultMode_", nb::is_arithmetic(), nb::is_flag());
#define BIND_IGFD_ENUM_VALUE(name) \
  e.value(#name, name);             \
  m.attr(#name) = IGFD_ResultMode_::name
    BIND_IGFD_ENUM_VALUE(IGFD_ResultMode_AddIfNoFileExt);
    BIND_IGFD_ENUM_VALUE(IGFD_ResultMode_OverwriteFileExt);
    BIND_IGFD_ENUM_VALUE(IGFD_ResultMode_KeepInputFile);
#undef BIND_IGFD_ENUM_VALUE
  }
}
