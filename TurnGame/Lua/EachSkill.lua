local ui = {}

-- set Initialize to avoid Output log print warning

function ui:Initialize() 
    self:BindButtonEvent()
end

function ui:BindButtonEvent()
    self.Learn.OnClicked:Add(function()
        local instance = self:GetMyInstance()
        instance:AddNewAbility(self.skill, self.ID)
        self:ResetVisibility()
    end);
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self:LoadDataTable()
    self.SkillIcon:SetBrushFromTexture(self.icon, true)
    self.SkillName:SetText(self.name)
    self:CheckSkillHasLearned()
end

function ui:CheckSkillHasLearned()
    if self:CheckSkillLearned() == true then
        self:ResetVisibility();
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

function ui:ResetVisibility()
    -- button hidden
    -- textblock visible

    self.Learn:SetVisibility(2)
    self.HasLearned:SetVisibility(0)
end

function ui:OnDestroy()
end

return ui