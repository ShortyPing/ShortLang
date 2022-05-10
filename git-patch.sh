date=$(date '+%d.%m.%Y %H:%M:%S')

git add --all
git commit -m "patch from $date pushed by $(whoami)"
git push -u origin master