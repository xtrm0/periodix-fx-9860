import json
datafile = open("data/elements.en.json")    
data = json.load(datafile)
f1 = open("../elemz.h", "w")
group = [0,1,18,1,2,13,14,15,16,17,18,1,2,13,14,15,16,17,18,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18]
period = [0,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7]
block =  [0,1,1,1,1,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,1,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,1,1,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,1,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,1,1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2]
btrans = [u'l', u's', u'p', u'd', u'f']
for i in range(len(group)):
    group[i]=u""+str(group[i])
for i in range(len(period)):
    period[i]=u""+str(period[i])
for i in range(len(block)):
    block[i]=btrans[block[i]]
print(len(group))
print(len(period))
print(len(block))

a = [0]
for i in data.keys():
    a.append(int(i))
a=sorted(a)
f1.write('''#ifndef ELEMZ_H
#define ELEMEZ_H
void gen_elements() {''')
for i in range(1,119):
    f1.write('''
    struct elem elem''' + str(i) + ''';''')
    
for j in a[1:119]:
    i=u""+str(j)
    f1.write('''
    elem''' + i + '''.Z=''' + i +''';
    elem''' + i + '''.a_w=''' + data[i]["atomic_weight"] +''';
    strncpy(elem''' + i + '''.e_config, "''' + data[i]["electronic_configuration"] +'''", sizeof(elem''' + i + '''.e_config)-1);
    elem''' + i + '''.e_config[29]=0;
    elem''' + i + ".X='" + data[i]["symbol"][0] +"'" + ''';
    elem''' + i + ".x='" + (data[i]["symbol"][1] if len(data[i]["symbol"])==2 else ''' ''') +"'" + ''';
    elem''' + i + '''.g=''' + group[j] +''';
    elem''' + i + '''.p=''' + period[j] +''';
    elem''' + i + ".b='" + block[j] +"';")

for i in range(1,119):
    f1.write('''ptable[''' + str(i) + '''] = elem''' + str(i) + ";" + '''
''')

f1.write('''}
#endif
''')
f1.close()
