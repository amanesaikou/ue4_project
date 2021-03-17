function Add(current, coefficient)
    return current + coefficient 
end

function IsSoulEnough(soulValue)
    if soulValue >= 0 then
        return true
    else
        return false
    end
end

local ui = {}

-- set Initialize to avoid Output log print warning

function ui:Initialize() 
    self:BindButtonEvent()
end

-- Bind button

function ui:BindButtonEvent()
    -- button close
    self.close.OnClicked:Add(function()
        self:SetHidden()
    end);

    -- button addHealth
    self.addHealth.OnClicked:Add(function()
        local soul = self.instance:GetSoul()
        local cost = (self.instance:GetLevel(0) + 1) * 20
        if IsSoulEnough(soul - cost) == true then
            self.instance:AddSoul(-cost)
            self.instance:AddLevel(0)
            local coefficient = self.instance:GetCoefficient(0)
            local currentHealth = self.player:GetHealth()
            local currentMaxHealth = self.player:GetMaxHealth() 
            self.player:SetHealth(Add(currentHealth, coefficient))
            self.player:SetMaxHealth(Add(currentMaxHealth, coefficient))
        end
    end);

    -- button addAttack
    self.addAttack.OnClicked:Add(function()
        local soul = self.instance:GetSoul()
        local cost = (self.instance:GetLevel(1) + 1) * 20
        if IsSoulEnough(soul - cost) == true then
            self.instance:AddSoul(-cost)
            self.instance:AddLevel(1)
            local coefficient = self.instance:GetCoefficient(1)
            local currentAttack = self.player:GetAttack()
            self.player:SetAttack(Add(currentAttack, coefficient))
        end
    end);

end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self:test()
    --self:BindButtomEvent()
end

function ui:OnDestroy()
end

return ui
