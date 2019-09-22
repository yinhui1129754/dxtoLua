path = require("path")
fs = require("fs")
var args = process.argv
if(!args.length>=4){
    throw "错误了,参数错误"
}
var name = args[3]
var classPath = path.join("./class");
var str = `
${name}Obj = {
    
   
}
${name}Obj.__index = ${name}Obj;
function ${name}Obj:new()
 local o = {}
 setmetatable(o,self)
 o.view = sprite:new(0,0,0,0)
 return o
end
function storeObj:init()

end
function ${name}Obj:render()

end

function ${name}Obj:frame(gsc)
   

end
`
if(args[2] == "class"){
    console.log("open:"+classPath+"/"+name+".lua")
    fs.openSync(classPath+"/"+name+".lua","a+")
    console.log("write:"+classPath+"/"+name+".lua")
    fs.writeFileSync(classPath+"/"+name+".lua",str)
}