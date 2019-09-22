array = {
    struct="array"
}
array.__index =  array;
function array:new()
    local o = {}
    setmetatable(o,self)
    o.value={}
    o.length=0
    return o
end
function array:endCall()
    self.length = #self.value;
end
function array:foreach(call)
    for i, v in ipairs(self.value) do 
        call(i,v)
    end 
    self:endCall();
end
function array:unforeach(call)
    local i =  #self.value
    while (i>=1) do
        call(i,self.value[i])
        i = i -1;
    end
end
function array:push(item)
    table.insert(self.value,item)
    self:endCall();
end
function array:unshift(item)
    table.insert(self.value,1,item)
    self:endCall();
end
function array:shift()
    local d =  table.remove(self.value,1)
    self:endCall();
    return d
end
function array:pop()
    local d = table.remove(self.value)
    self:endCall();
    return d;
end
function array:concat(arr)
    local Self = self
    arr:foreach(function (i,item)
        Self:push(item)
    end)
    self:endCall();
end
function array:remove(index)
  
    table.remove(self.value,index)
end
function array:insert(index,item)
    table.insert(self.value,index,item)
end
--Æ´½ÓÎª×Ö·û´®
function  array:join(sign)
    local str = "";
    self:foreach(function(i,item)
        str=str..sign..tostring(item)
    end)
    return str;
end