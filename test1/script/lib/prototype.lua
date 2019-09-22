--只适用于字符串和数字表
table.get_set_fun = (function ()
    local bufIndexTab = 1
    local value = {}
   return function (tab,tabObj)
        if not( tabObj ) then
            return;
        end
        local tabIndex = -1;
        if not( tab["get_set_index"] ) then
            tab["get_set_index"] = bufIndexTab
        end
        tabIndex = "a"..tab["get_set_index"]
        bufIndexTab=bufIndexTab+1;
        for i, v in pairs(tab) do
            value[tabIndex..i] = v
        end
        local obj = {
            __index=function(t,k)
                if tabObj and tabObj[k] and tabObj[k]["get"] then
                    tabObj[k]["get"]( value[tabIndex..k],k);
                end
                return value[tabIndex..k]
            end,
            __newindex=function(t, k, v)
                local before =  value[tabIndex..k]
                value[tabIndex..k] = v
                if tabObj and  tabObj[k] and tabObj[k]["set"] then
                    tabObj[k]["set"]( value[tabIndex..k] ,before,k)
                end
                return t;
            end
        }
        setmetatable(tab,obj)
    end
end)()

math.round = function(num, i)
    local mult = 10^(i or 0)
    local mult10 = mult * 10
    return math.floor((num * mult10 + 5)/10)/ mult
end
string.guid = function()
    local seed={'e','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'}
    local tb={}
    for i=1,32 do
        table.insert(tb,seed[math.random(1,16)])
    end
    local sid=table.concat(tb)
    return string.format('%s-%s-%s-%s-%s',
        string.sub(sid,1,8),
        string.sub(sid,9,12),
        string.sub(sid,13,16),
        string.sub(sid,17,20),
        string.sub(sid,21,32)
    )
end