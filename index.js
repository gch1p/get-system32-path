'use strict'

const nativeModule = require('./build/Release/get-system32-path.node')

module.exports = {
  GetSystem32Path() {
    return nativeModule.GetSystem32Path()
  }
}
