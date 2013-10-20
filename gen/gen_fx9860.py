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
#define ELEMZ_H
''')

def pregen(a, b, c):
    f1.write('''void gen_elements'''+str(c)+'''() {''')
    for i in range(a,b):
        f1.write('''
    struct elem elem''' + str(i) + ''';''')
        
def gene(j):
    i=u""+str(j)
    f1.write('''
    elem''' + i + '''.Z=''' + i +''';
    elem''' + i + '''.a_w=''' + data[i]["atomic_weight"] +''';
    strncpy(elemnames[''' + i + '''], "''' + data[i]["name"] +'''", sizeof(char)*17);
    elemnames[''' + i + '''][16]=0;
    strncpy(elemconfig[''' + i + '''], "''' + data[i]["electronic_configuration"] +'''", sizeof(char)*21);
    elemconfig[''' + i + '''][21]=0;
    elem''' + i + ".X='" + data[i]["symbol"][0] +"'" + ''';
    elem''' + i + ".x='" + (data[i]["symbol"][1] if len(data[i]["symbol"])==2 else ''' ''') +"'" + ''';
    elem''' + i + '''.Ei=''' + (data[i]["ionization_potential"] if data[i]["ionization_potential"]!='na' else '0') +''';
    elem''' + i + '''.Eae=''' + data[i]["electron_afinity"] +''';
    elem''' + i + '''.En=''' + (data[i]["pauling_negativity"] if data[i]["pauling_negativity"]!='na' else '0') +''';
    elem''' + i + '''.r=''' + (data[i]["atomic_radius"] if data[i]["atomic_radius"]!='na' else '0') +''';
    elem''' + i + '''.g=''' + group[j] +''';
    elem''' + i + '''.p=''' + period[j] +''';
    elem''' + i + ".b='" + block[j] +"';")

def postgen(a,b):
    for i in range(a,b):
        f1.write('''
    ptable[''' + str(i) + '''] = elem''' + str(i) + ";")
    f1.write('''}
''')

pregen(1,119,1)
for j in a[1:119]:
    gene(j)
postgen(1,119)

#pregen(30,60,2)
#for j in a[30:60]:
#    gene(j)
#postgen(30,60)

#pregen(60,90,3)
#for j in a[60:90]:
#    gene(j)
#postgen(60,90)

#pregen(90,119,4)
#for j in a[90:119]:
#    gene(j)
#postgen(90,119)

f1.write('''
#endif
''')
f1.close()
