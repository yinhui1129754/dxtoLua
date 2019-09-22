screen = {
    viewArray=array:new(), --´æ·Å¾«ÁéµÄ
    frameArray=array:new(),
    view = sprite:new(0,0,0,0),
    bg = sprite:new(0,0,0,0),
    top = sprite:new(0,0,0,0),
    w=800,
    h=600
}
screen.__index = screen
function screen:new()
    local o = {}
    setmetatable(o,self)
    o.viewArray = array:new()
    o.frameArray = array:new()
    o.view = sprite:new(0,0,0,0)
    o.bg = sprite:new(0,0,0,0)
    o.top = sprite:new(0,0,0,0)
    o.viewArray:push(o.bg)
    o.viewArray:push(o.view)
    o.viewArray:push(o.top)
  
    return o;
end
function screen:render()
    local Self  =self;
    self.viewArray:foreach(function(i,item)
      
        item:render(Self);
       
    end)
end
function screen:frame()
    local Self = self;
    self.frameArray:foreach(function(i,item)
      
        item:frame(Self);
       
    end)
end
function screen:add(item)
    self.viewArray:push(item)
end
function screen:addBg(item)
    self.bg:addChild(item);
end
function screen:addView(item)
    self.view:addChild(item);
end
function screen:addTop(item)
    self.top:addChild(item);
end
function screen:remove(item)
    local Self  =self;
    self.viewArray:unforeach(function(i,v)
        if(item == v) then
            Self.viewArray:remove(i);
        end
    end)
end
function screen:removeIndex(i)
    self.viewArray:remove(i);
end