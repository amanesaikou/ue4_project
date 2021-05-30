-- 導入庫
local KismetTextLibrary = import("KismetTextLibrary")
local KismetStringLibrary = import("KismetStringLibrary")

local typeChange = {}
TypeChange = typeChange

function TypeChange.IntToFText(num)
    local content = KismetStringLibrary.Conv_IntToString(num)
    content = KismetTextLibrary.Conv_StringToText(content)
    return content
end
--[[
function TypeChange.FStringToFText(str)
    local content = KismetTextLibrary.Conv_StringToText(str)
    return content
end
]]
return typeChange