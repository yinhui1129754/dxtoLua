storeObj = {
   view=sprite:new(0,0,0,0),
   maxWidth=123,
   maxAngle = 360,
   centerX = 0,
   centerY = 0,
   k = 0,
}
storeObj.__index = storeObj;
function storeObj:new()
    
    o = {}
    setmetatable(o,self)
  
    o.view=sprite:new(0,0,0,0)
    o.view.img="source/img/store.png"
    o.centerX = 0
    o.centerY = 0
    o.k = 0;
    return o
end
function storeObj:init()
    local randomInfo = self.maxWidth * math.random()
    randomInfo = math.round(randomInfo);
    if randomInfo<=50 then
        randomInfo = 50
    end
    self.view.angle = math.round(self.maxAngle * math.random())
    self.view.w = randomInfo
    self.view.h = randomInfo
end
function storeObj:initPos(gsc)
    local random = math.random();
    if random<0.25 then
        self:initTop(gsc);
    elseif random>=0.25 and random <0.5 then
        self:initBottom(gsc);
    elseif random >=0.5 and random <0.75 then
        self:initLeft(gsc);
    else 
        self:initRight(gsc);
    end
    self.centerX = gsc.w/2-self.view.w/2;
    self.centerY = gsc.h/2-self.view.h/2;
    self.k =  (self.view.g_y - self.centerY)/(self.view.g_x - self.centerX)
end
function storeObj:initTop(gsc)
   local x  = gsc.w*math.random();
   x = math.round(x);
   self.view:setY(-self.view.h);
   self.view:setX(x);
end
function storeObj:initBottom(gsc)
    local x  = gsc.w*math.random();
    x = math.round(x);
    self.view:setY(gsc.h);
    self.view:setX(x);
end
function storeObj:initLeft(gsc)
    local y  = gsc.h*math.random();
    y = math.tointeger(y);
    self.view:setX(-self.view.w);
    self.view:setY(y);
end
function storeObj:initRight(gsc)
    local y  = gsc.h*math.random();
    y = math.tointeger(y);
    self.view:setX(gsc.w);
    self.view:setY(y);
end
function storeObj:frame(gsc)
    
    if(self.view.g_x>self.centerX+1) then
        self.view:setX(self.view.g_x-1)
        self.view:setY(self.view.g_y-self.k)
    elseif (self.view.g_x<self.centerX-1) then
        self.view:setX(self.view.g_x+1)
        self.view:setY(self.view.g_y+self.k)
    else 
        self.view:setX(self.centerX)
        self.view:setY(self.centerY)
    end
 
    self.view.angle = self.view.angle + 1;
end