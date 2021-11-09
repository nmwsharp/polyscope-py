import polyscope_bindings as psb

from polyscope.core import glm3, glm4

# === Text

def TextUnformatted(s):
    psb.TextUnformatted(s)


# === Inputs

def Button(label_str):
    return psb.Button(label_str)

def Checkbox(label_str, checked):
    return psb.Checkbox(label_str, checked)

def InputInt(label_str, val, step=1, step_fast=100):
    return psb.InputInt(label_str, val, step, step_fast)

def InputFloat(label_str, val, step=0., step_fast=0., format="%.6f"):
    return psb.InputFloat(label_str, val, step, step_fast, format)

def SliderFloat(label_str, val, v_min, v_max, format="%.3f", power=1.0):
    return psb.SliderFloat(label_str, val, v_min, v_max, format, power)

def ColorEdit3(label_str, color3, NoInputs=False):
    changed, out = psb.ColorEdit3(label_str, glm3(color3), NoInputs)
    return changed, out.as_tuple()

def ColorEdit4(label_str, color4, NoInputs=False):
    changed, out = psb.ColorEdit4(label_str, glm4(color4), NoInputs)
    return changed, out.as_tuple()

def InputText(label_str, value_str):
    return psb.InputText(label_str, value_str)

def BeginCombo(label_str, preview_str):
    return psb.BeginCombo(label_str, preview_str)

def Selectable(label_str, selected):
    return psb.Selectable(label_str, selected)

def EndCombo():
    psb.EndCombo()


# === Posiitioning / Sizing / Layout

def Separator():
    psb.Separator()

def SameLine():
    psb.SameLine()
  
def NewLine():
    psb.NewLine()

def Indent(width):
    psb.Indent(width)

def Unindent(width):
    psb.Unindent(width)

def PushItemWidth(width):
    psb.PushItemWidth(width)

def PopItemWidth():
    psb.PopItemWidth()

def PushID(id_str):
    psb.PushID(id_str)

def PopID():
    psb.PopID()

def TreeNode(label_str, DefaultOpen=True):
    return psb.TreeNode(label_str, DefaultOpen)

def TreePop():
    return psb.TreePop()
