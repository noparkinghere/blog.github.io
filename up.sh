#! /bin/bash

git pull origin master
echo "hexo build and run the shell for pushing your blog to github"
git add .
git commit -m "update blog"
git push origin master
