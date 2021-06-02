local ui = {}

function ui:Initialize()
    self:BindButtonEvent()
end

-- 按鈕事件綁定
function ui:BindButtonEvent()
    self.enhanceButton.OnClicked:Add(function()
        local cost = self.equipment:GetEnhancementCost()
        local spiritStone = self.sect:GetSpiritStone()
        if self.equipment:Enhance(spiritStone) == true then
            self.sect:UseSpiritStone(cost)
            self:Rebuild()
        end
    end);

    self.closeButton.OnClicked:Add(function()
        self.equipmentContent:SetVisibility(0)
        self:RemoveFromViewport()
    end);
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self:SetSect()
    self:Rebuild()
end

function ui:Rebuild()
    self:SetEnhanceLevel()
    self:SetCost()
    self:SetSpiritStoneNum()
    self.equipmentContent:Rebuild()
end

function ui:SetEnhanceLevel()
    local level = self.equipment:GetEnhancementLevel()
    self.enhanceLevel:SetText('強化+'..tostring(level))
end

function ui:SetCost()
    local level = self.equipment:GetEnhancementLevel()
    if level < 20 then
        local cost = self.equipment:GetEnhancementCost()
        self.cost:SetText('強化至下一級須耗費'..tostring(cost)..'靈石')
    else
        self.cost:SetText('已強化到最高級別')
    end
end

function ui:SetSpiritStoneNum()
    local spiritStone = self.sect:GetSpiritStone()
    self.allSpiritStone:SetText('目前共有'..tostring(spiritStone)..'靈石')
end

function ui:Destruct()
    self.enhanceButton.OnClicked:Clear()
    self.closeButton.OnClicked:Clear()
    self.enhanceButton = nil
    self.closeButton = nil
    self.equipment = nil
    self.enhanceLevel = nil
    self.cost = nil
    self.allSpiritStone = nil
    self.sect = nil
end

function ui:OnDestroy()
end

return ui