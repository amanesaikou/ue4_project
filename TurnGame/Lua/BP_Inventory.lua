local ui = {}

-- set Initialize to avoid Output log print warning

function ui:Initialize()
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
end

function ui:OnMouseEnter(geometry, event)
    -- IDの値はゼロなら、つまりアイテムがない。
    if self.item.ID ~= 1000 then
        self:CreateInfoUi()
        self.itemInfo:AddToViewport(2)
        local mousePoisition = self:GetMousePosition()
        self.itemInfo:SetPositionInViewport(mousePoisition, false)
    end
end

function ui:OnMouseButtonDown(geometry, event)
    if self:IsRightMouseDown(event) == true then
        if self.item.hasEquipped == false and self.item.ID ~= 0 then
            if self.item.itemType > -1 then  --and self.item.itemType < 8 then
                self:CreateActionUi()
                self.Action:AddToViewport(3)
                local mousePoisition = self:GetMousePosition()
                self.Action:SetPositionInViewport(mousePoisition, false)
            end
        elseif self.item.ID ~= 0 then
            self:CreateTakeOffUi()
            self.TakeOffUi:AddToViewport(3)
            local mousePoisition = self:GetMousePosition()
            self.TakeOffUi:SetPositionInViewport(mousePoisition, false)
        end
    end
end

function ui:OnMouseLeave(event)
    if self.itemInfo ~= nil then
        self.itemInfo:RemoveFromViewport()
        self.itemInfo = nil
    end
end

function ui:OnDestroy()
end

return ui