local ui = {}

-- set Initialize to avoid Output log print warning

function ui:Initialize() 
end

-- 建立說話者的名字與圖片對照表
-- 讀取劇情
-- 顯示一開始的劇情
-- 話している者の名前と画像の比較表を作成する
-- ストーリーを読み込む
-- 最初のテキストを示す

function ui:Construct()
    self.bHasScriptImplementedTick = true
    self:SetCharTable()
    self:SetDialogueTable()
    self:Change()
end

function ui:Change()
    if self.index == self.words:Num()  then
        self:RemovefromParent()
    else
        self:ChangeText()
        self:ChangeImage()
        self.index = self.index + 1
    end
end

function ui:ChangeText()
    self.content:SetText(self.words:Get(self.index))
    if self.name:Get(self.index) == 'background' then
        self.CharacterName:SetText('')
    else
        self.CharacterName:SetText(self.name:Get(self.index))
    end
 end

 function ui:ChangeImage()
    local index = self.backgroundIndex:Get(self.index)
        self.background:SetBrushFromTexture(self.backgroundImages:Get(index),true)
    if self.name:Get(self.index) == 'background' then
        self:SetHidden()
    else
        self:SetVisible()
        self:ChoiceImage()
    end
end

function ui:ChoiceImage()
    for i,v in pairs(self.NameTable) do
        if self.name:Get(self.index) == v then
            self.character:SetBrushFromTexture(self.ImageTable:Get(i), true)
        end
    end
end

-- 改變顯示的角色圖片與文字
-- キャラクターの画像とテキストを変更する

function ui:OnMouseButtonDown(Geometry, Event)
    self:Change()
end

-- 檢查是否使用skip功能
-- スキップしたいの？

function ui:Tick(dt)
    -- skip ui 是否建立
    -- skip ui 是否在畫面中
    -- skip ui內 藉由 IsSkip判斷要跳過劇情還是不要
    if self.skip ~= nil then 
        if self.skip:IsInViewport() == false then 
            if self.skip.IsSkip == true then 
                self:RemovefromParent()
            end
        end
    end
end

function ui:OnDestroy()
end


return ui