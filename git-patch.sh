date=$(date '+%d.%m.%Y %H:%M:%S')

commitChanges=""

for changes in "$@"
do
  commitChanges="$commitChanges $changes"
done

git add --all
git commit -m "patch from $date pushed by $(whoami)" -m "$commitChanges"
git push -u origin master