let disposable1 = vscode.commands.registerCommand(
    'extension.camelStyle',
    function() {
      // 编辑器对象
      const editor = vscode.window.activeTextEditor
      // 获取所有选中文本
      const allSelections = editor.selections

      editor.edit(editBuilder => {
        // 遍历并替换文本
        allSelections.forEach(selection => {
          const text = editor.document.getText(selection)
          editBuilder.replace(selection, toCamelCase(text))
        })
      })
    }
  )
