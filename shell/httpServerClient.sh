#!/bin/bash

# 测试命令执行时间
root="127.0.0.1:38501/"
testCount=10000
urlParam=(
"GetDefaultServer" $testCount
"GetServerList" $testCount
"GetRecommendServerList" $testCount
"UpdateServerState" $testCount
"CreateRole" $testCount
"DeleteRole" $testCount
"ChangeRoleName" $testCount
"RoleLevelUp" $testCount
)
urlParamLen=${#urlParam[@]}

getURL()
{
	local timeBegin=$[$(date +%s%N)/1000000]
	local i=1
	local len=$2
	local url="$root$1"
	for i in $(seq 1 $len); do
		curl -o /dev/null -s "$url"
		# curl "$url"
	done
	local timeEnd=$[$(date +%s%N)/1000000]
	local timeUse=$((timeEnd-timeBegin))
	local timeAvg=$((timeUse/len))
	echo "url:$url;次数:$len;总耗时:$timeUse(毫秒);每条耗时:$timeAvg(毫秒)"
}

main()
{
	local i=0
	for ((i=0; i<$urlParamLen; i=i+2)); do
		getURL ${urlParam[i]} ${urlParam[i+1]}
	done
}

main
