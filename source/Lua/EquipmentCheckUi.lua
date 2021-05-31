local ui = {}

function ui:Initialize()
    self:BindButtonEvent()
end

-- 按鈕事件綁定
function ui:BindButtonEvent()
    self.yesButton.OnClicked:Add(function()
        local type = self.equipment:GetType()
        if type == 0 then
            self:UseWeapon()
        elseif type == 1 then
            self:UseArtifact()
        elseif type == 2 then
            self:UseHiddenWeapon()
        end
        self:RemoveFromViewport()
    end);

    self.noButton.OnClicked:Add(function()
        self:RemoveFromViewport()
    end);
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self:SetSect()
    self:SetText()
end

function ui:SetText()
    local name = self.equipment:GetName()
    self.useText:SetText('你確定要裝備'..name..'嗎?')
end

function ui:UseWeapon()
    local weapons = self.sect:GetWeapons()
    self.disciple:WearEquipment(weapons, self.index)
end

function ui:UseArtifact()
    local artifacts = self.sect:GetArtifacts()
    self.disciple:WearEquipment(artifacts, self.index)
end

function ui:UseHiddenWeapon()
    local hiddenWeapons = self.sect:GetHiddenWeapons()
    self.disciple:WearEquipment(hiddenWeapons, self.index)
end

function ui:Destruct()
    self.yesButton.OnClicked:Clear()
    self.noButton.OnClicked:Clear()
    self.yesButton = nil
    self.noButton = nil
    self.useText = nil
    self.setting:Rebuild()
    self.setting:SetVisibility(0)
    print(collectgarbage("count"))
end

function ui:OnDestroy()
end

return ui