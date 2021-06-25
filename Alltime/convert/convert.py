
import json
  
f = open('dataset.json')
  
# returns JSON object as 
# a dictionary
data = json.load(f)
 
for i in data:
    item = data[i]
    observable = item["observable"]
    xtitle = item["xtitle"]
    particle = item["particle"]
    collision = item["collision"]
    energy = item["energy"]
    collab = item["collab"]
    observable = item["observable"]
    observable = item["observable"]
    observable = item["observable"]
    print(data[i]["reference"])
    print("---------------")
  
# Closing file
f.close()
