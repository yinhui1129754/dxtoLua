createObj = {
    --[[
        ʯͷ��������
    ]]
   stroeArr=array:new(), --����ʯͷ������
   createMaxStroeTime = 5, --����ʯͷ�����ʱ����
   createNowStroeTime = 0, --����ʯͷ�ĵ�ǰʱ�� 
   maxStoreNumber = 30,
   removeStoreNumber = 30
}
createObj.__index = createObj;
function createObj:new()
 o = {}
 setmetatable(o,self)
 return o
end
function createObj:render()

end
function createObj:createStore(gsc)
   
    info = storeObj:new();
    info:init();
    gsc:addView(info.view);
   
    info:initPos(gsc);
    
    self.stroeArr:push(info)
    if(self.stroeArr.length>=self.removeStoreNumber) then
       local d=  self.stroeArr:shift();
       gsc.view:removeChild(d.view)
        self.maxStoreNumber = self.maxStoreNumber+1
    end
end
function createObj:frame(gsc)
    self.stroeArr:foreach(function(i,item)
        
        item:frame(gsc)
     
    end)
    if (self.createNowStroeTime<=0 and self.maxStoreNumber>=0) then
        self.createNowStroeTime = self.createMaxStroeTime;
        r = math.random();
        
        if (r<0.75) then
            self:createStore(gsc);
            self.maxStoreNumber = self.maxStoreNumber -1 
        end
    else 
        self.createNowStroeTime = self.createNowStroeTime - 1;
    end
   
end