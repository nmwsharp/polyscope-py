import polyscope_bindings as psb

# === Text

def TextUnformatted(s):
    psb.TextUnformatted(s)


# === Inputs

def Button(s):
    return psb.Button(s)

def Checkbox(s, b):
    return psb.Checkbox(s, b)

def InputInt(s, v, step=1, step_fast=100):
    return psb.InputInt(s, v, step, step_fast)

def InputFloat(s, v, step=0., step_fast=0., format="%.6f"):
    return psb.InputFloat(s, v, step, step_fast, format)

def SilderFloat(s, v, v_min, v_max, format="%.3f", power=1.0):
    return psb.SliderFloat(s, v, v_min, v_max, format, powr)

def InputText(s, v):
    return psb.InputText(s, v)


# === Posiitioning / Sizing / Layout

def Separator():
    psb.Separator()

def SameLine():
    psb.SameLine()
  
def NewLine():
    psb.NewLine()

def Indent():
    psb.Indent()

def Unindent():
    psb.Unindent()

def PushItemWidth(w):
    psb.PushItemWidth(w)

def PopItemWidth(w):
    psb.PopItemWidth(w)

def PushID(s):
    psb.PushID(s)

def PopID():
    psb.PopID()

def TreeNode(s, DefaultOpen=True):
    return psb.TreeNode(s, DefaultOpen)

def TreePop():
    return psb.TreePop()
