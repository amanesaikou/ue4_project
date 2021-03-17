local ui = {}

-- set Initialize to avoid Output log print warning

function ui:Initialize() 
    self:BindButtonEvent()
end

function ui:BindButtonEvent()
    self.Wear.OnClicked:Add(function()
        if self.inventory.item.itemType < 8 then
            local instance = self:GetMyInstance()
            instance:DeleteItem(self.inventory.index)
            local newItem = instance:WearEquipment(self.inventory.item)
            instance:SetItemIndex(newItem, self.inventory.index)
            self.inventory:Clear()
            self.inventory:SetItem(newItem)
        end
        self:RemoveFromViewport()
    end);

    self.Sell.OnClicked:Add(function()
        self:CreateSellUi()
        self:RemoveFromViewport()
    end);
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self:Timer()
end

function ui:OnDestroy()
end

return ui
