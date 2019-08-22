import os
n = 0
for root, dirs, files in os.walk('./'):
 for name in files:
  if((name.endswith(".vcxproj") or name.endswith(".vcxproj.filters")) and not name.find(".vs2010")>=0):
   n += 1
   print(n)
   os.rename(os.path.join(root, name),os.path.join(root, name.replace('vcxproj','vs2010.vcxproj')))
