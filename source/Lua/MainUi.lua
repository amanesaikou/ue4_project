local ui = {}

function ui:Initialize()
    self:BindButtonEvent()
end

-- 按鈕事件綁定
function ui:BindButtonEvent()
    self.discipleButton.OnClicked:Add(function()
        self:ComponentHidden()
        self:ShowAllDiscipleUi()
    end);

    self.lawButton.OnClicked:Add(function()
        self:ComponentHidden()
        self:ShowAllLawUi()
    end);

    self.equipmentButton.OnClicked:Add(function()
        self:ComponentHidden()
        self:ShowAllEquipmentUi()
    end);
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
end

--[[
        Visible = 0
        Collapsed = 1
        Hidden = 2
        HitTestInvisible = 3
        SelfHitTestInvisible = 4
    }
    --]]

-- 隱藏組件
function ui:ComponentHidden()
    self.discipleButton:SetVisibility(2)
    self.equipmentButton:SetVisibility(2)
    self.lawButton:SetVisibility(2)
    self.enemy:SetVisibility(2)
end

-- 顯示組件
function ui:ComponentVisible()
    self.discipleButton:SetVisibility(0)
    self.equipmentButton:SetVisibility(0)
    self.lawButton:SetVisibility(0)
    self.enemy:SetVisibility(0) 
end

function ui:Destruct()
    self.discipleButton.OnClicked:Clear()
    self.equipmentButton.OnClicked:Clear()
    self.lawButton.OnClicked:Clear()
    self.discipleButton = nil
    self.equipmentButton = nil
    self.lawButton = nil
    self.allDisciple = nil
    print('mainui', collectgarbage("count"))
end

function ui:OnDestroy()
end

return ui