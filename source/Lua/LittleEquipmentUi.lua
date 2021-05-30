local ui = {}

function ui:Initialize()
    self:BindButtonEvent()
end

-- 按鈕事件綁定
function ui:BindButtonEvent()
    self.useButton.OnClicked:Add(function()
        if self.canSell == false then
            self:ShowCheckUi()
            self.useEquipment:RemoveFromViewport()
        end
    end);
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self:SetImage()
end

function ui:Destruct()
    self.useButton.OnClicked:Clear()
    self.useButton = nil
end

function ui:OnDestroy()
end

return ui