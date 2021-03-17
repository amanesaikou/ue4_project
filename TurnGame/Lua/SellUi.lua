function CanSell(current, sell)
    if sell == 0 or sell > current then
        return false
    else
        return true
    end
end

local ui = {}

-- set Initialize to avoid Output log print warning

function ui:Initialize() 
    self:BindButtonEvent()
end

function ui:BindButtonEvent()
    self.Yes.OnClicked:Add(function()
    local currentQuantity = self:GetItemQuantity()
    local quantity = self:GetInputQuantity()
    if CanSell(currentQuantity, quantity) == true then
        local index = self:GetItemIndex()
        self.instance:SellItem(index, quantity)
        self.actionUi.inventory:SubQuantity(quantity)
        if self:GetItemQuantity() == 0 then
            self.instance:DeleteItem(index)
            self.actionUi.inventory:Clear()
            --self:RemoveFromViewport()
        else
            self.actionUi.inventory:ShowQuantity()
            --self:RemoveFromViewport()
        end
    end
    self:RemoveFromViewport()
    end);

    self.No.OnClicked:Add(function()
        self:RemoveFromViewport()
    end);
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self:CreateGameInstance()
    self:SetText()
end

function ui:SetText()
    if self:CanOverlap() == true then
        self.SellText:SetText('どの数量を売りたいか')
        self:SetInputVisible()
    else
        self.SellText:SetText('これを売りたいか')
    end
end

function ui:CanOverlap()
    if self.actionUi.inventory:CanOverlap() == true then
        return true
    else
        return false
    end
end

    --[[
    enum ESlateVisibility {
        Visible = 0
        Collapsed = 1
        Hidden = 2
        HitTestInvisible = 3
        SelfHitTestInvisible = 4
    }
    --]]

function ui:SetInputVisible()
    self.Input:SetVisibility(0)
end

function ui:GetItemQuantity()
    return self.actionUi.inventory:GetQuantity()
end

function ui:GetItemIndex()
    return self.actionUi.inventory.index
end

function ui:OnDestroy()
end

return ui
