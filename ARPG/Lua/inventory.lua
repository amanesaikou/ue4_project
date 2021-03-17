local ui = {}

-- 導入資料型態轉換的庫

local KismetTextLibrary = import("KismetTextLibrary")
local KismetStringLibrary = import("KismetStringLibrary")
local KismetMathLibrary = import("KismetMathLibrary")

-- set Initialize to avoid Output log print warning

function ui:Initialize()
end

-- set tick

function ui:Construct()
    self.bHasScriptImplementedTick = true
end


-- 顯示物品資料

function ui:OnMouseEnter(geometry, event)
    if self:IsEmpty() == false then
        self.info = slua.loadUI('/Game/Ui/Inventory/ItemInformation.ItemInformation')
        self.info.image = self:GetImage()
        self.info.name = self:GetName()
        self.info.introduction = self:GetContent()
        self.info:AddToViewport(0)
    end
end

function ui:OnMouseLeave(event)
    self:RemoveInfoUi()
end

-- 刪除物品資訊的ui

function ui:RemoveInfoUi()
    if self.info ~= nil and self.info:IsInViewport() == true then
        self.info:RemoveFromViewport()
        self.info = nil
        print('remove successfully')
    end
end

-- 將text轉成uint8

function ui:ToByte(quantity)
    local quantity = KismetTextLibrary.Conv_TextToString(quantity)
    quantity = KismetStringLibrary.Conv_StringToInt(quantity)
    quantity = KismetMathLibrary.Conv_IntToByte(quantity)

    return quantity
end


function ui:Tick(dt)
    if self.DropWidget ~= nil then
        if self.DropWidget.clicked == true then
            local quantity = self.DropWidget.InputBox:GetText()
            --local quantity = self:GetByte(quantity)
            --quantity = KismetTextLibrary.Conv_TextToString(quantity)
            --quantity = KismetStringLibrary.Conv_StringToInt(quantity)
            --quantity = KismetMathLibrary.Conv_IntToByte(quantity)
            --self:Drop(quantity)
            self:Drop(self:ToByte(quantity))
            self.DropWidget.clicked = false
            self.DropWidget = nil
            self:RemoveInfoUi()
        end
    end
end

function ui:OnDestroy()
end

return ui