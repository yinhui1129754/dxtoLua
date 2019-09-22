
require("script\\lib\\prototype")
require("script\\lib\\array")
require("script\\lib\\sprite")
require("script\\lib\\screen")
require("script\\class\\store")
require("script\\class\\star")
require("script\\class\\create")

g_screen = screen:new();
window.showconsole();
window.setwidth(screen.w)
window.setheight(screen.h)

--bg
sprite1 = sprite:new(0,0,g_screen.w,g_screen.h);
g_screen:addBg(sprite1)
sprite1.img = "source/bg/bg.jpg"

--mousemove事件
addMouseEvent("mousemove","mouseeventCall")

--create对象
g_createObj = createObj:new()
g_screen.frameArray:push(g_createObj)
--中间球体对象
g_star = starObj:new();
g_screen:addTop(g_star.view);
g_star:init(g_screen);


--资源加载相关
imgNum = 0;
isLoaded = false
function endLoadImg()
    imgNum=imgNum+1
    if(imgNum == 3) then
      
        isLoaded = true
    end
end
loadImg("source/img/phone.png","endLoadImg")
loadImg("source/bg/bg.jpg","endLoadImg")
loadImg("source/img/store.png","endLoadImg")
function drawFrame()
    if(isLoaded) then
        g_screen:render();
    end
end

function frame()
    if(isLoaded) then
        g_screen:frame();
    end
end
function mouseeventCall(x,y)
  
end