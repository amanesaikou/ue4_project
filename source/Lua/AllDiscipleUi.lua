local ui = {}

function ui:Initialize()
    self:BindButtonEvent()
end

-- 按鈕事件綁定
function ui:BindButtonEvent()
    self.closeButton.OnClicked:Add(function()
        self:RemoveFromViewport()
    end);

    self.addDiscipleButton.OnClicked:Add(function()
        if self.sect:CanEmployDisciple() == true then
            self.sect:EmployEliteDisciple()
            self:Rebuild()
        end
    end);

    self.sortButton.OnClicked:Add(function()
        self.sect:DiscipleSort()
        print('aftersort', collectgarbage("count"))
        self:Rebuild()
        print('afterbuild', collectgarbage("count"))
    end);
    
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self:SetSect()
    self:Rebuild()
end

function ui:Destruct()
    self.main:ComponentVisible()
    self.closeButton.OnClicked:Clear()
    self.addDiscipleButton.OnClicked:Clear()
    self.sortButton.OnClicked:Clear()
    self.closeButton = nil
    self.addDiscipleButton = nil
    self.sortButton = nil
    self.sect = nil
    self.wrapBox:ClearChildren()
    self.wrapBox = nil
    print('allui', collectgarbage("count"))
end

function ui:OnDestroy()
    print('allui', collectgarbage("count"))
end

return ui