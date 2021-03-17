local ui = {}

-- set Initialize to avoid Output log print warning

function ui:Initialize()
end

function ui:Construct()
    self.bHasScriptImplementedTick = true
    print('test')
    --self:SetPlayer()
    self:SetStyle()
    self:SetTimer()
end

function ui:OnDestroy()
end

return ui