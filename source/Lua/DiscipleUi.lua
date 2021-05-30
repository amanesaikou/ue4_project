local TypeChange = require ("TypeChange")

local ui = {}

function ui:Initialize()
    self:BindButtonEvent()
end

-- 按鈕事件綁定
function ui:BindButtonEvent()
    self.settingButton.OnClicked:Add(function()
        self:ShowDiscipleSetting()
        self.allDisciple:SetVisibility(2)
    end);
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self:SetColor()
    self:SetText()
end

-- 設定文字內容
function ui:SetText()
    local name = self.disciple:GetName()
    self.nameText:SetText(name)
    index = TypeChange.IntToFText(self.index+1)
    self.indexText:SetText(index)
end

--[[
    Visible = 0
    Collapsed = 1
    Hidden = 2
    HitTestInvisible = 3
    SelfHitTestInvisible = 4
]]

function ui:OnMouseEnter(geometry, event)
    self.border:SetVisibility(3)
end

function ui:OnMouseLeave(geometry, event)
    self.border:SetVisibility(2)
end

function ui:Destruct()
    self.settingButton.OnClicked:Clear()
    self.settingButton = nil
    self.nameText = nil
    self.indexText = nil
    self.disciple = nil
    self.border = nil
    print(collectgarbage("count"))
end

function ui:OnDestroy()
end

return ui