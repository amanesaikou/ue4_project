local ui = {}

function ui:Initialize()
    self:BindButtonEvent()
end

-- 按鈕事件綁定
function ui:BindButtonEvent()
    self.closeButton.OnClicked:Add(function()
        self.setting:SetVisibility(0)
        self:RemoveFromViewport()
    end);
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self:SetTypeText()
    self:ShowLittleEquipment()
end

-- 根據物品種類修改上方文字
function ui:SetTypeText()
    if self.index == 1 then
        self.type:SetText('武器') 
    elseif self.index == 2 then
        self.type:SetText('法寶') 
    elseif self.index == 3 then
        self.type:SetText('暗器')
    end
end

function ui:Destruct()
    self.equipments = nil
    self.type = nil
    self.index = nil
end

function ui:OnDestroy()
end

return ui