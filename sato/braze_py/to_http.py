# import http.server
# import socketserver
import requests




def getStatus(Lsholder):
    #(間に合わなかったら怖いので[0,0] なら立ってて,それ以外なら座ってるようにしておく)
    if (Lsholder[0]==0)&(Lsholder[1]==0):
        return "stand"
    else:
        return "sit"    

def httpreq(Lsholder,past_stat):

    status=getStatus(Lsholder)
   # print(status)
    if status==past_stat:
#        print("⭐︎"+status)
        return status

    else:
        print("status change to:"+status+'______')
        if status=='sit':
            r = requests.get('http://localhost:3000/v1?trigger=sit')
        elif status=='stand':
            r = requests.get('http://localhost:3000/v1?trigger=stand')

        return status



#http://localhost:3000/v1?trigger=sit
#http://localhost:3000/v1?trigger=sitting

#http://localhost:3000/v1?trigger=stand


