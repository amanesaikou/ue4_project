local ui = {}

function ui:Initialize()
    self:BindButtonEvent()
end

-- 按鈕事件綁定
function ui:BindButtonEvent()
    self.weaponButton.OnClicked:Add(function()
        self.index = 1
        self:Rebuild()
    end);

    self.artifactButton.OnClicked:Add(function()
        self.index = 2
        self:Rebuild()
    end);

    self.hiddenWeaponButton.OnClicked:Add(function()
        self.index = 3
        self:Rebuild()
    end);

    self.sortButton.OnClicked:Add(function()
        self.sect:EquipmentSort(self.index)
        self:Rebuild()
        print('EquipmentSort', collectgarbage("count"))
    end);

    self.closeButton.OnClicked:Add(function()
        self.mainUi:ComponentVisible()
        self:RemoveFromViewport()
    end);
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self:SetSect()
    self:Rebuild()
end

function ui:Rebuild()
    self.wrapBox:ClearChildren()
    if self.index == 1 then
        self:CreateLittleEquipmentUi(self.sect:GetWeapons())
    elseif self.index == 2 then
        self:CreateLittleEquipmentUi(self.sect:GetArtifacts())
    elseif self.index == 3 then
        self:CreateLittleEquipmentUi(self.sect:GetHiddenWeapons())
    end
    print('Rebuild', collectgarbage("count"))
end

function ui:Destruct()
    self.weaponButton.OnClicked:Clear()
    self.artifactButton.OnClicked:Clear()
    self.hiddenWeaponButton.OnClicked:Clear()
    self.sortButton.OnClicked:Clear()
    self.closeButton.OnClicked:Clear()
    self.weaponButton = nil
    self.artifactButton = nil
    self.hiddenWeaponButton = nil
    self.sortButton = nil
    self.closeButton = nil
    self.index = nil
    self.wrapBox:ClearChildren()
    self.wrapBox = nil
    self.sect = nil
    print('AllEquipment', collectgarbage("count"))
end

function ui:OnDestroy()
end

return ui