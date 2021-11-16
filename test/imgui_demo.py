import polyscope as pscope
from polyscope import imgui


pscope.set_program_name("Demo")
pscope.init()
pscope.set_up_dir("z_up")


def cb():
    imgui.SetNextItemOpen(True, imgui.ImGuiCond_FirstUseEver)
    if imgui.TreeNode("Trees"):
        imgui.SetNextItemOpen(True, imgui.ImGuiCond_FirstUseEver)
        if imgui.TreeNode("Basic trees"):
            for i in range(5):
                imgui.SetNextItemOpen(True, imgui.ImGuiCond_FirstUseEver)
                if imgui.TreeNode(f"child {i}"):
                    imgui.Text("blah blah")
                    imgui.SameLine()
                    if imgui.SmallButton("button"):
                        pass
                    imgui.TreePop()
            imgui.TreePop()


pscope.set_user_callback(cb)

pscope.show()
