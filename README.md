# little-tools
跨平台小工具集合

## 依赖：
wxWidgets: https://github.com/wxWidgets/wxWidgets

## 编译


### 跨平台
夸 pc 平台编译移动端，从 iOS 来看，不是很靠谱，太多兼容问题。
所以改框架首先用来实现 linux 、 mac、 windows 互通


#### 编译到 iOS - deprecated
```iOS
cmake .. -G Xcode -DCMAKE_TOOLCHAIN_FILE=../ios.cmake ..
```

```xcodeproj
cmake .. -G Xcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphoneos
```