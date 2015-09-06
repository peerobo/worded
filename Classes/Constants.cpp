 #include "Constants.h"
#include "cocos2d.h"

const char* Constants::ASS_BG_INTRO = "intro";
const char* Constants::ASS_BG_ONE = "onebg";
const char* Constants::ASS_BG_TABLE = "tablebg";

const char* Constants::ASS_FNT_NORMAL = "worded.fnt";
const char* Constants::ASS_FNT_BIG = "score.fnt";

// suffix
const char* Constants::ASS_SUFFIX_DATA = ".plist";
const char* Constants::ASS_SUFFIX_IMAGE = ".png";
const char* Constants::ASS_SUFFIX_IMAGE_JPG = ".jpg";
const char* Constants::ASS_SUFFIX_TEXATL = ".pvr.ccz";

const char* Constants::ASS_TEX_GUI = "gui";

const char* Constants::CONST_CIDR[33] = {
		"0.0.0.0",
		"128.0.0.0",
		"192.0.0.0",
		"224.0.0.0",
		"240.0.0.0",
		"248.0.0.0",
		"252.0.0.0",
		"254.0.0.0",
		"255.0.0.0",
		"255.128.0.0",
		"255.192.0.0",
		"255.224.0.0",
		"255.240.0.0",
		"255.248.0.0",
		"255.252.0.0",
		"255.254.0.0",
		"255.255.0.0",
		"255.255.128.0",
		"255.255.192.0",
		"255.255.224.0",
		"255.255.240.0",
		"255.255.248.0",
		"255.255.252.0",
		"255.255.254.0",
		"255.255.255.0",
		"255.255.255.128",
		"255.255.255.192",
		"255.255.255.224",
		"255.255.255.240",
		"255.255.255.248",
		"255.255.255.252",
		"255.255.255.254",
		"255.255.255.255"
};

const char* Constants::CONST_IP_RANGE[327] = {
	"1.52.0.0/14",
	"5.10.84.184/29",
	"14.0.16.0/20",
	"14.160.0.0/11",
	"14.224.0.0/11",
	"27.0.12.0/22",
	"27.2.0.0/15",
	"27.64.0.0/12",
	"27.118.16.0/20",
	"42.1.64.0/18",
	"42.96.0.0/22",
	"42.96.4.0/23",
	"42.96.6.0/24",
	"42.96.7.0/24",
	"42.96.8.0/24",
	"42.96.9.0/24",
	"42.96.10.0/23",
	"42.96.12.0/22",
	"42.96.16.0/20",
	"42.96.32.0/19",
	"42.112.0.0/13",
	"49.156.52.0/22",
	"49.213.64.0/18",
	"49.236.208.0/22",
	"49.246.128.0/18",
	"49.246.192.0/19",
	"58.186.0.0/15",
	"61.11.224.0/19",
	"61.28.224.0/19",
	"66.117.9.112/29",
	"101.53.0.0/18",
	"101.96.12.0/22",
	"101.96.64.0/18",
	"101.99.0.0/18",
	"103.1.200.0/22",
	"103.1.208.0/22",
	"103.1.236.0/22",
	"103.2.220.0/22",
	"103.2.224.0/22",
	"103.2.228.0/22",
	"103.3.244.0/22",
	"103.3.248.0/22",
	"103.3.252.0/22",
	"103.4.128.0/22",
	"103.5.30.0/23",
	"103.5.204.0/22",
	"103.5.208.0/22",
	"103.7.36.0/22",
	"103.7.40.0/22",
	"103.7.172.0/24",
	"103.7.174.0/23",
	"103.7.177.0/24",
	"103.7.196.0/24",
	"103.8.13.0/24",
	"103.9.0.0/22",
	"103.9.4.0/22",
	"103.9.76.0/22",
	"103.9.80.0/22",
	"103.9.84.0/22",
	"103.9.196.0/22",
	"103.9.200.0/22",
	"103.9.204.0/22",
	"103.9.208.0/22",
	"103.9.212.0/22",
	"103.10.88.0/22",
	"103.10.212.0/22",
	"103.11.172.0/22",
	"103.12.104.0/22",
	"103.13.76.0/22",
	"103.15.48.0/22",
	"103.16.0.0/22",
	"103.17.88.0/22",
	"103.17.236.0/22",
	"103.18.4.0/22",
	"103.18.176.0/22",
	"103.19.96.0/22",
	"103.19.164.0/22",
	"103.19.220.0/22",
	"103.20.144.0/22",
	"103.20.148.0/22",
	"103.21.120.0/22",
	"103.21.148.0/22",
	"103.23.144.0/22",
	"103.23.156.0/22",
	"103.24.244.0/22",
	"103.26.252.0/22",
	"103.27.60.0/22",
	"103.27.64.0/22",
	"103.27.236.0/22",
	"103.28.32.0/22",
	"103.28.36.0/22",
	"103.28.136.0/22",
	"103.28.172.0/22",
	"103.30.36.0/22",
	"103.31.120.0/22",
	"103.31.124.0/22",
	"103.37.28.0/22",
	"103.37.32.0/22",
	"103.38.136.0/22",
	"103.39.92.0/22",
	"103.39.96.0/22",
	"103.224.168.0/22",
	"103.225.236.0/22",
	"103.226.108.0/22",
	"103.226.248.0/22",
	"103.227.112.0/22",
	"103.227.216.0/22",
	"103.228.20.0/22",
	"103.229.40.0/22",
	"103.229.192.0/22",
	"103.231.148.0/22",
	"103.231.188.0/22",
	"103.232.52.0/22",
	"103.232.56.0/22",
	"103.232.60.0/22",
	"103.232.120.0/22",
	"103.233.48.0/22",
	"103.234.36.0/22",
	"103.234.88.0/22",
	"103.235.208.0/22",
	"103.235.212.0/22",
	"103.237.60.0/22",
	"103.237.64.0/22",
	"103.237.96.0/22",
	"103.237.144.0/22",
	"103.237.148.0/22",
	"103.238.68.0/22",
	"103.238.72.0/22",
	"103.238.76.0/22",
	"103.238.80.0/22",
	"103.238.208.0/22",
	"103.238.212.0/22",
	"103.239.32.0/22",
	"103.239.116.0/22",
	"103.239.120.0/22",
	"103.241.248.0/22",
	"103.242.52.0/22",
	"103.243.104.0/22",
	"103.243.216.0/22",
	"103.244.136.0/22",
	"103.245.148.0/22",
	"103.245.244.0/22",
	"103.245.248.0/22",
	"103.245.252.0/22",
	"103.246.104.0/24",
	"103.246.220.0/22",
	"103.248.160.0/22",
	"103.248.164.0/22",
	"103.249.20.0/22",
	"103.249.100.0/22",
	"103.250.24.0/22",
	"103.252.0.0/22",
	"103.252.252.0/22",
	"103.253.88.0/22",
	"103.254.12.0/22",
	"103.254.16.0/22",
	"103.254.40.0/22",
	"103.254.216.0/22",
	"103.255.84.0/22",
	"103.255.236.0/22",
	"110.35.64.0/21",
	"110.35.72.0/21",
	"110.44.184.0/21",
	"111.65.240.0/20",
	"111.91.232.0/22",
	"112.72.64.0/18",
	"112.78.0.0/20",
	"112.109.88.0/21",
	"112.137.128.0/20",
	"112.197.0.0/16",
	"112.213.80.0/20",
	"113.20.96.0/19",
	"113.22.0.0/16",
	"113.23.0.0/17",
	"113.52.32.0/19",
	"113.61.108.0/22",
	"113.160.0.0/11",
	"115.72.0.0/13",
	"115.84.176.0/21",
	"115.146.120.0/21",
	"115.165.160.0/21",
	"116.68.128.0/21",
	"116.96.0.0/12",
	"116.118.0.0/17",
	"116.193.64.0/20",
	"116.212.32.0/19",
	"117.0.0.0/13",
	"117.103.192.0/18",
	"117.122.0.0/17",
	"118.68.0.0/14",
	"118.102.0.0/21",
	"118.107.64.0/18",
	"119.15.160.0/19",
	"119.17.192.0/18",
	"119.18.128.0/20",
	"119.18.184.0/21",
	"119.82.128.0/20",
	"120.50.184.0/21",
	"120.72.80.0/21",
	"120.72.96.0/19",
	"120.138.64.0/20",
	"122.102.112.0/22",
	"122.129.0.0/18",
	"122.201.8.0/21",
	"123.16.0.0/12",
	"124.157.0.0/18",
	"124.158.0.0/20",
	"125.58.0.0/18",
	"125.212.128.0/17",
	"125.214.0.0/18",
	"125.234.0.0/15",
	"125.253.112.0/20",
	"171.224.0.0/11",
	"175.103.64.0/18",
	"175.106.0.0/22",
	"180.93.0.0/16",
	"180.148.0.0/21",
	"180.148.128.0/20",
	"180.214.236.0/22",
	"182.161.80.0/20",
	"182.236.112.0/22",
	"182.237.20.0/22",
	"183.80.0.0/16",
	"183.81.0.0/17",
	"183.90.160.0/21",
	"183.91.0.0/19",
	"183.91.160.0/19",
	"192.95.41.112/28",
	"192.95.49.172/30",
	"192.95.53.80/28",
	"192.95.58.176/30",
	"202.0.79.0/24",
	"202.4.168.0/24",
	"202.4.176.0/24",
	"202.6.2.0/24",
	"202.6.96.0/23",
	"202.9.79.0/24",
	"202.9.80.0/24",
	"202.9.84.0/24",
	"202.37.86.0/23",
	"202.43.108.0/22",
	"202.44.137.0/24",
	"202.47.87.0/24",
	"202.47.142.0/24",
	"202.52.39.0/24",
	"202.55.132.0/22",
	"202.56.57.0/24",
	"202.58.245.0/24",
	"202.59.238.0/23",
	"202.59.252.0/23",
	"202.60.104.0/21",
	"202.74.56.0/24",
	"202.74.58.0/23",
	"202.78.224.0/21",
	"202.79.232.0/21",
	"202.87.212.0/22",
	"202.92.4.0/22",
	"202.93.156.0/22",
	"202.94.82.0/24",
	"202.94.88.0/23",
	"202.124.204.0/24",
	"202.130.36.0/23",
	"202.134.16.0/21",
	"202.134.54.0/24",
	"202.151.160.0/20",
	"202.158.244.0/22",
	"202.160.124.0/23",
	"202.172.4.0/23",
	"202.191.56.0/22",
	"203.8.127.0/24",
	"203.8.172.0/24",
	"203.34.144.0/24",
	"203.77.178.0/24",
	"203.79.28.0/24",
	"203.89.140.0/22",
	"203.99.248.0/22",
	"203.113.128.0/19",
	"203.113.160.0/19",
	"203.119.8.0/22",
	"203.119.36.0/22",
	"203.119.44.0/22",
	"203.119.58.0/23",
	"203.119.60.0/22",
	"203.119.64.0/21",
	"203.119.72.0/22",
	"203.128.240.0/21",
	"203.160.0.0/23",
	"203.160.96.0/21",
	"203.161.178.0/24",
	"203.162.0.0/21",
	"203.162.8.0/21",
	"203.162.16.0/20",
	"203.162.32.0/19",
	"203.162.64.0/18",
	"203.162.128.0/20",
	"203.162.144.0/20",
	"203.162.160.0/19",
	"203.162.192.0/18",
	"203.163.128.0/18",
	"203.170.26.0/23",
	"203.171.16.0/20",
	"203.176.160.0/21",
	"203.189.28.0/22",
	"203.190.160.0/20",
	"203.191.8.0/21",
	"203.191.48.0/21",
	"203.195.0.0/18",
	"203.201.56.0/22",
	"203.205.0.0/18",
	"203.209.180.0/22",
	"203.210.128.0/18",
	"203.210.192.0/18",
	"210.2.64.0/18",
	"210.86.224.0/20",
	"210.211.96.0/19",
	"210.245.0.0/19",
	"210.245.32.0/19",
	"210.245.64.0/18",
	"218.100.10.0/24",
	"218.100.14.0/24",
	"218.100.60.0/24",
	"220.231.64.0/18",
	"221.121.0.0/18",
	"221.132.0.0/18",
	"221.133.0.0/19",
	"222.252.0.0/14",
	"223.27.104.0/21"
};
