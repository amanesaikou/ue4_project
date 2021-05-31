local TypeChange = require ("TypeChange")

local ui = {}

function ui:Initialize()
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self:SetEqtipmentName()
    self:SetAllLevel()
    self:SetImage()
    self:SetAttribute()
end

-- 設置裝備名稱與階級
function ui:SetEqtipmentName()
    local text = self.equipment:GetName()..' '..self.equipment:GetRarityName()
    self.equipmentName:SetText(text)
end

-- 設置強化與精煉等級
function ui:SetAllLevel()
   local enhance = self.equipment:GetEnhancementLevel()
   local refine = self.equipment:GetRefiningLevel()
   local str = '強化+'..tostring(enhance)..' '..'精煉+'..tostring(refine)
   self.allLevel:SetText(str)
end

-- 設置屬性
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
    self.data:SetText('+'..tostring(num))
    self.attributeType:SetText(text)
end

function ui:Destruct()
    self.equipment = nil
    self.data = nil
    self.attributeType = nil
    self.allLevel = nil
    print(collectgarbage("count"))
end

function ui:OnDestroy()
end

return ui