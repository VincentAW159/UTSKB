#buat dulu nodesnya
#program akan meminta state

#program menggunakan A*
#pertama di masukkan dlu, di check apakah sesuai goalstate
#kalau gk sesuai goalstate maka akan mengexpand dengan melihat posible move, dan dari setiap posible move di hitung heuristiknya+depth
#nanti di masukkan di queue dan di sorting berdasarkan nilaiCostnya dan yang terkecil di dahulukan sehingga menemukan jawaban

#class untuk menyimpan state dll
class node: #untuk class puzzle
    def __init__(self, state, parent, move, depth, cost, heur):
        self.state = state #ini untuk state yang sekarang berada
        self.parent = parent #ini untuk kalau ada parent
        self.move = move #ini untuk movenya antara naik / turun / kanan / kiri
        self.depth = depth #ini kedalaman dimana puzzle ini berada misal di anakan 1 jadi depthnya 1
        self.cost = cost #ini untuk tau berapa langkah dari state pertama hingga state skarang
        self.heur = heur #total nilai heuristik + depthnya
        if self.state:
            self.map = ''.join(str(e) for e in self.state) # ini buat di jadiin string karena nanti pengecheckannya menggunakan string

#global variable
GoalState = [] #ini untuk menyimpan goalstate yang di inginkan
goalNode = None #ini untuk menyimpan hasil goal dari AI untuk di loopkan biar tau langkahnya
NodesExpanded = 0 #ini untuk mengetahui berapa node yang di bikin untuk mencari jawabannya
MaxSearchDeep = 0 #ini untuk mengetahui berapa dalam maximum 

#function
def Heuristic(node): #ini untuk menghitung heuristiknya
    to_return = 0
    for i in range(0,9):
        if (node[i] == goalData[i]):
            to_return += 0 #ini kalau data[i]nya sesuai dengan goal[i]nya maka di tambah 0
        else :
            to_return += 1 #kalau tidak sesusai maka ditambahkan 1
    return to_return


#bikin anakan
def subNodes(nd):

    global NodesExpanded
    NodesExpanded = NodesExpanded+1
     #jadi ini ceritanya untuk menambahkan subnodenya di setiap ndoe yang dimasukkan dalam parameter, dan akan 
     #dibuat dimasukkan 1 per 1 setiap movenya nanti movenya di check pake fungsi move
     #dimana kalau memang ngga bisa akan di returnkan statenya null
     #ketika sudah di tambahkan nanti di check apakah null / tidak sehingga dimasukkan dalam list(arraynya python) dan nanti akan di returnkan list yang berisikan state yang dapat di jalani
    nextPaths = []
    nextPaths.append(node(move(nd.state, 1), nd, 1, nd.depth + 1, nd.cost + 1, 0)) #(node(state, parent, move, depth, cost, heur))
    nextPaths.append(node(move(nd.state, 2), nd, 2, nd.depth + 1, nd.cost + 1, 0))
    nextPaths.append(node(move(nd.state, 3), nd, 3, nd.depth + 1, nd.cost + 1, 0))
    nextPaths.append(node(move(nd.state, 4), nd, 4, nd.depth + 1, nd.cost + 1, 0))
    nodes=[]
    for procPaths in nextPaths:
        if(procPaths.state!=None):
            nodes.append(procPaths)
    return nodes

#function untuk move:
def move(state, direction):
    #di copy dahulu
    newState = state[:]

    #ini untuk mencari di indexmana 0 berada jadi yang di movekan ini adalah 0 nya
    index = newState.index(0)

    if(index==0): #berada di pojok kiri atas 0 nya
        if(direction==1): 
            return None                          #1 - up
        if(direction==2):                       #2 - down
            temp=newState[0]                    #3 - left
            newState[0]=newState[3]             #4 - right
            newState[3]=temp
        if(direction==3):
            return None
        if(direction==4):
            temp=newState[0]
            newState[0]=newState[1]
            newState[1]=temp
        return newState      
    if(index==1):#berada di tengah atas 0 nya
        if(direction==1):
            return None
        if(direction==2):
            temp=newState[1]
            newState[1]=newState[4]
            newState[4]=temp
        if(direction==3):
            temp=newState[1]
            newState[1]=newState[0]
            newState[0]=temp
        if(direction==4):
            temp=newState[1]
            newState[1]=newState[2]
            newState[2]=temp
        return newState    
    if(index==2): #berada di pojok kanan atas 0 nya
        if(direction==1):
            return None
        if(direction==2):
            temp=newState[2]
            newState[2]=newState[5]
            newState[5]=temp
        if(direction==3):
            temp=newState[2]
            newState[2]=newState[1]
            newState[1]=temp
        if(direction==4):
            return None
        return newState
    if(index==3):#berada di pojok kiri tengah 0 nya
        if(direction==1):
            temp=newState[3]
            newState[3]=newState[0]
            newState[0]=temp
        if(direction==2):
            temp=newState[3]
            newState[3]=newState[6]
            newState[6]=temp
        if(direction==3):
            return None
        if(direction==4):
            temp=newState[3]
            newState[3]=newState[4]
            newState[4]=temp
        return newState
    if(index==4): #berada di tengah tengah 0 nya
        if(direction==1):
            temp=newState[4]
            newState[4]=newState[1]
            newState[1]=temp
        if(direction==2):
            temp=newState[4]
            newState[4]=newState[7]
            newState[7]=temp
        if(direction==3):
            temp=newState[4]
            newState[4]=newState[3]
            newState[3]=temp
        if(direction==4):
            temp=newState[4]
            newState[4]=newState[5]
            newState[5]=temp
        return newState
    if(index==5):#berada di pojok kanan tengah 0 nya
        if(direction==1):
            temp=newState[5]
            newState[5]=newState[2]
            newState[2]=temp
        if(direction==2):
            temp=newState[5]
            newState[5]=newState[8]
            newState[8]=temp
        if(direction==3):
            temp=newState[5]
            newState[5]=newState[4]
            newState[4]=temp
        if(direction==4):
            return None
        return newState
    if(index==6):#berada di pojok kiri bawah 0 nya
        if(direction==1):
            temp=newState[6]
            newState[6]=newState[3]
            newState[3]=temp
        if(direction==2):
            return None
        if(direction==3):
            return None
        if(direction==4):
            temp=newState[6]
            newState[6]=newState[7]
            newState[7]=temp
        return newState
    if(index==7):#berada di tengah bawah 0 nya
        if(direction==1):
            temp=newState[7]
            newState[7]=newState[4]
            newState[4]=temp
        if(direction==2):
            return None
        if(direction==3):
            temp=newState[7]
            newState[7]=newState[6]
            newState[6]=temp
        if(direction==4):
            temp=newState[7]
            newState[7]=newState[8]
            newState[8]=temp
        return newState
    if(index==8):#berada di pojok kanan bawah 0 nya
        if(direction==1):
            temp=newState[8]
            newState[8]=newState[5]
            newState[5]=temp
        if(direction==2):
            return None
        if(direction==3):
            temp=newState[8]
            newState[8]=newState[7]
            newState[7]=temp
        if(direction==4):
            return None
        return newState

#ai using a*
def AI(startingState):
    global  MaxSearchDeep, GoalNode #global karena saya deklarasinya secara global

    state = ""
    for tmp in startingState:
        state += str(tmp)  #dari state yang berisikan list dijadikan sebuah string, supaya lebih gampang ngeceknya
    
    key = Heuristic(state) # ngitung heuristik dari awal state
    boardVisited = set()  #ini untuk nanti ngecheck apakah pernah dikunjungi atau tidak biar tidak loop di situ terus
    Queue = [] #ini queue untuk menampung node node yang akan di cek
    Queue.append(node(startingState, None, None, 0, 0, key)) #diapend dahulu
    boardVisited.add(state) #dan dimasukkan kedalam visited

    while Queue:
        Queue.sort(key=lambda o: o.heur) #untuk mensorting key value ( heur + depth )
        nd = Queue.pop(0)                   # untuk mengambil dan juga menghapus queue yang paling depan setelah di sorting
        if nd.state == GoalState: #checking apakah sudah sampai goalstate atau belum
            GoalNode = nd         
            return Queue 
        posiblePaths = subNodes(nd) #ini untuk mendapatkan possible movenya / anakannya dari node yang berada di awal queue
        for path in posiblePaths:   #karena di return dalam bentuk list(array) maka di check juga pakah nodenya pernah ada di visited board atau tidak
            thisPath = path.map[:]
            if thisPath not in boardVisited: #ini checknya kalau ngga ada baru di masukin ke queue lagi dan akan begini terus sampai ketemu jawabannya
                key = Heuristic(path.map)
                path.key = key + path.depth
                Queue.append(path)               
                boardVisited.add(path.map[:])
                if path.depth > MaxSearchDeep:
                    MaxSearchDeep = 1 + MaxSearchDeep

data = input("input data = ")
data = data.split(" ")
for i in range(0, len(data)): #ini untuk input starting statenya, karena python itu kalau inputan pasti string jadi jadikan int dengan int() dan dijadikan array
    data[i] = int(data[i])
print(data)

goalData = input("input goalstate: ") #sama seperti starting state cuman ini untuk goalstatenya
goalData = goalData.split(" ")
for i in range(0, len(goalData)):
    GoalState.append(int(goalData[i]))

print(GoalState)

AI(data)

deep = GoalNode.depth
moves = []
while data != GoalNode.state: #ini hanya untuk mendapatkan move dari Ai yang mencapai goalstate dan akan di loop hingga ke starting state
    if GoalNode.move == 1:
        path = 'Up'
    if GoalNode.move == 2:
        path = 'Down'
    if GoalNode.move == 3:
        path = 'Left'
    if GoalNode.move == 4:
        path = 'Right'
    moves.insert(0, path)  #dimasukkan dari depan karena kita loopnya dari bawah ke atas
    GoalNode = GoalNode.parent

#print hasil
print("path: ",moves)
print("cost: ",len(moves))
print("nodes expanded: ",str(NodesExpanded))
print("search_depth: ",str(deep))
print("MaxSearchDeep: ",str(MaxSearchDeep))
