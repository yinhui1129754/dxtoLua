starObj = {
    view = sprite:new(0,0,0,0)
}
starObj.__index = starObj;
function starObj:new()
 o = {}
 setmetatable(o,self)
 o.view = sprite:new(0,0,0,0)
 o.view.img = "source/img/phone.png"
 return o
end
function starObj:init(gsc)
    self.view.w = 200
    self.view.h = 200
    self.view:setX(gsc.w/2-self.view.w/2);
    self.view:setY(gsc.h/2-self.view.h/2);
end

function starObj:frame(gsc)

end