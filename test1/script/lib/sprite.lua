--¾«Áé¶ÔÏó
sprite = {
    x=0,
    y=0,
    w=0,
    h=0,
    g_x=0,
    g_y=0,
    color=0xffffff
  
}
sprite.__index = sprite
function sprite:new (x,y,w,h)
    local o = {}
    setmetatable(o,self)
    o.x = x
    o.w = w
    o.h = h
    o.y = y
    o.g_x = x
    o.g_y = y
    o.color = 0xffffff
    o.children = array:new()
    o.parent = nil
    o.img = ""
    o.angle = 0;
    o.rotateX = 0.5;
    o.rotateY = 0.5;
    o.id = string.guid();
    return o
end

function sprite:render (scn)
    draw.save()
    
    draw.rotate(self.angle,self.g_x+self.w*self.rotateX,self.g_y+self.h*self.rotateY)
   
    if not(self.img == "") then
        draw.drawImg(self.img,self.g_x,self.g_y,self.w,self.h);
    else
        draw.fillStyle(self.color,1.0)
        draw.fillRect(self.g_x,self.g_y,self.w,self.h)
    end

   
    if(self.children.length>0) then
        
        self.children:foreach(function(i,item)
            item:render(scn);
        end)
    end
    draw.restore()
end
function sprite:initX()
    if(self.parent)then
        self.g_x = self.parent.g_x + self.x;
    end
end
function sprite:initY()
    if(self.parent)then
        self.g_y = self.parent.g_y + self.x;
    end
end
function sprite:addChild(sp)
    sp.parent = self;
    sp:initX();
    sp:initY();
    self.children:push(sp);
end
function sprite:removeChild(item)
    local Self  =self;
    item.parent = nil;
    self.children:unforeach(function(i,v)
       
        if(item == v) then
            self.children:remove(i);
        end
    end)
end
function sprite:setX(val)
    self.g_x = val;
    local Self = self;
    if(self.children.length) then
        Self.children:foreach(function(i,item)
            item:initX();
        end)
    end
end
function sprite:setY(val)
    self.g_y = val;
    local Self = self;
    if(self.children.length) then
        Self.children:foreach(function(i,item)
            item:initY();
        end)
    end
end