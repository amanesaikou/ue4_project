local TypeChange = require ("TypeChange")

local ui = {}

function ui:Initialize()
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self:SetEqtipmentName()
    self:SetImage()
    self:SetAttribute()
end

function ui:SetEqtipmentName()
    local text = self.equipment:GetName()..' '..self.equipment:GetRarityName()
    self.equipmentName:SetText(text)
end

function ui:SetAttribute()
    local attack = self.equipment:GetFinallyAttack()
    local health = self.equipment:GetFinallyHealth()
    local defense = self.equipment:GetFinallyDefense()
    if attack > 0 then
        self:SetAttributeText('傷害', attack)
    elseif health > 0 then
        self:SetAttributeText('氣血', health)
    elseif defense > 0 then
        self:SetAttributeText('防禦', defense)
    end
end

function ui:SetAttributeText(text, num)
    self.data:SetText('+'..TypeChange.IntToFText(num))
    self.attributeType:SetText(text)
end

function ui:Destruct()
    self.equipment = nil
    self.data = nil
    self.attributeType = nil
    print(collectgarbage("count"))
end

function ui:OnDestroy()
end

return ui