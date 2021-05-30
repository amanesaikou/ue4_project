local TypeChange = require ("TypeChange")

local ui = {}

function ui:Initialize()
    self:BindButtonEvent()
end

-- 按鈕事件綁定
function ui:BindButtonEvent()
    self.closeButton.OnClicked:Add(function()
        self:RemoveFromViewport()
    end);   

    self.expelButton.OnClicked:Add(function()
        local sect = self:GetSect()
        if sect:CanExpelDisciple(self.index) == true then
            sect:ExpelDisciple(self.index)
            self.allDisciple:Rebuild()
            self:RemoveFromViewport()
        end
    end); 
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self:Rebuild()
    self:SetText()
    self:SetTextColor()
end

function ui:Rebuild()
    self:SetCultivationLaw()
    self:SetWorkoutLaw()
    self:SetAttackSkill()
    self:SetWeapon()
    self:SetArtifact()
    self:SetHiddenWeapon()
    self:SetAttriute()
end

function ui:SetText()
    self:SetRarity()
    self:SetLifePalace()
    self:SetStar()
end

function ui:SetAttriute()
    self:SetHealth()
    self:SetAttack()
    self:SetDefense()
end

function ui:SetRarity()
    local rarity = self.disciple:GetRarityName()
    self.rarityName:SetText(rarity)
end

function ui:SetLifePalace()
    local lifePalaceTitle = self.disciple:GetLifePalaceTitle()
    self.lifePalace:SetText(lifePalaceTitle)
    local num = self.disciple:GetLifePalace()
    local lifePalaceNum = ' x '..tostring(num)
    self.lifePalaceNum:SetText(lifePalaceNum)
end

function ui:SetStar()
    local starPalaceTitle = self.disciple:GetStarTitle()
    self.starName:SetText(starPalaceTitle)
    local num = self.disciple:GetStar()
    local starNum = ' x '..tostring(num)
    self.starNums:SetText(starNum)
end

function ui:SetHealth()
    local health = self.disciple:GetFinallyHealth()
    self.health:SetText(TypeChange.IntToFText(health))
end

function ui:SetAttack()
    local attack = self.disciple:GetFinallyAttack()
    self.attack:SetText(TypeChange.IntToFText(attack))
end

function ui:SetDefense()
    local defense = self.disciple:GetFinallyDefense()
    self.defense:SetText(TypeChange.IntToFText(defense))
end


function ui:Destruct()
    print(collectgarbage("count"))
    self.allDisciple:SetVisibility(0)
    self:Clear()
    print(collectgarbage("count"))
end

function ui:Clear()
    self.closeButton.OnClicked:Clear()
    self.closeButton = nil
    self.disciple = nil
    self.rarityName = nil
    self.lifePalace = nil
    self.lifePalaceNum = nil
    self.starName = nil
    self.starNums = nil
    self.health = nil
    self.attack = nil
    self.defense = nil
    self.index = nil
end

function ui:OnDestroy()
end

return ui