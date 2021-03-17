--[[
    enum class EItemType : uint8 {
	Helmet		= 0		UMETA(DisplayName = "Helmet"),
	Armor		= 1		UMETA(DisplayName = "Armor"),
	Necklace	= 2		UMETA(DisplayName = "Necklace"),
	Gloves		= 3		UMETA(DisplayName = "Gloves"),
	Weapon		= 4		UMETA(DisplayName = "Weapon"),
	Ring		= 5		UMETA(DisplayName = "Ring"),
	Belt		= 6		UMETA(DisplayName = "Belt"),
	Shoes		= 7		UMETA(DisplayName = "Shoes"),
	HPPotion	= 8		UMETA(DisplayName = "HPPotion"),
	MPPotion	= 9		UMETA(DisplayName = "MPPotion"),
	Material	= 10	UMETA(DisplayName = "Material"),
};
]]

function FloatToInt(value)
    return math.floor(value)
end

function Rarity(rarity)
    local text = ''
    if rarity == 1 then
        text = 'normal'
    elseif rarity == 2 then
        text = 'excellent'
    elseif rarity == 3 then
        text = 'rare'
    elseif rarity == 4 then
        text = 'legend'
    end
    return text
end

function Health(attribute, itemType)
    local text = ''
    if attribute.health > 0.0 then
        if itemType == 8 then 
            text = 'HPを'..FloatToInt(attribute.health)..'回復'
        else
            text = '最大HP + '..FloatToInt(attribute.health)
        end
    end
    return text
end

function Mana(attribute, itemType)
    local text = ''
    if attribute.mana > 0.0 then
        if itemType == 9 then 
            text = 'MPを'..FloatToInt(attribute.mana)..'回復'
        else
            text = '最大MP + '..FloatToInt(attribute.mana)
        end
    end
    return text
end

function Attack(attribute, itemType)
    local text = ''
    if attribute.attack > 0.0 then
        text = '攻撃力 + '..FloatToInt(attribute.attack)
    end
    return text
end

function Defense(attribute, itemType)
    local text = ''
    if attribute.defense > 0.0 then
        text = '防御力 + '..FloatToInt(attribute.defense)
    end
    return text
end

function SellPrice(price)
    local text = ''
    text = '販売価格は'.. price
    return text
end

local ui = {}

-- set Initialize to avoid Output log print warning

function ui:Initialize() 
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self.ItemName:SetText(self.item.name)
    self.Icon:SetBrushFromTexture(self.item.icon, true)
    self:SetQuantity()
    self:CreatePropertyText()
end

function ui:SetQuantity()
    if self.item.canOverlap == true then
        self.Quantity:SetText(self.item.currentQuantity)
    end
end

function ui:CreatePropertyText()
    self:CreateTextUi(Rarity(self.item.rarity))
    self:CreateTextUi(Health(self.item.attribute, self.item.itemType))
    self:CreateTextUi(Mana(self.item.attribute, self.item.itemType))
    self:CreateTextUi(Attack(self.item.attribute, self.item.itemType))
    self:CreateTextUi(Defense(self.item.attribute, self.item.itemType))
    self:CreateTextUi(SellPrice(self.item.price))
end


function ui:CreateTextUi(text)
    if text ~= '' then
        property = slua.loadUI('/Game/Ui/Property.Property')
        property.Text:SetText(text)
        self.ArrtubeInfo:AddChild(property)
    end
end

function ui:OnDestroy()
end

return ui