/**
  * ���ܣ�������Ĳ��롢ɾ��������
  * �����롿�����뵽ָ��Ԫ�غ�
  * 1�����Ҹ�Ԫ���Ƿ���ڣ�
  * 2��û���ҵ����� -1
  * 3���ҵ����д�����㲢��������
  *
  * �����ҡ�����ֵ����/����������
  * 1���жϵ�ǰ����Ƿ����null�����Ƿ���ڸ���ֵ��
  * 2���ж��Ƿ�����ҵ���ֵ��
  * 3��û���ҵ����� -1��
  * 4���ҵ���ֵ���ؽ�㣻
  *
  * ��ɾ��������ֵɾ��
  * 1���ж��Ƿ��ҵ���ֵ��
  * 2���ҵ���¼ǰ��㣬����ɾ����
  * 3���Ҳ���ֱ�ӷ���-1��
  */
 //������
 class Node{
	    constructor(data){
		        this.data = data;
		        this.next = null;
		
	}
	 }

//��������
class LinkList{
	    constructor(){
		        //��ʼ��ͷ���
			        this.head = new Node('head');
		
	}
	
		    //���� value ���ҽ��
		    findByValue = (value) = >{
		       let currentNode = this.head;
		        while (currentNode != = null && currentNode.data != = value){
			            currentNode = currentNode.next;
			
		}
		        //�жϸý���Ƿ��ҵ�
			        console.log(currentNode)
			        return currentNode == = null ? -1 : currentNode;
		    }
	
		    //���� index ���ҽ��
		    findByIndex = (index) = >{
		        let pos = 0;
		        let currentNode = this.head;
		        while (currentNode != = null && pos != = index){
			            currentNode = currentNode.next;
			            pos++;
			
		}
		        //�ж��Ƿ��ҵ�������
			        console.log(currentNode)
			        return currentNode == = null ? -1 : currentNode;
		    }
	
	    //����Ԫ��(ָ��Ԫ��������)
		    insert = (value, element) = >{
		        //�Ȳ��Ҹ�Ԫ��
			        let currentNode = this.findByValue(element);
		        //���û���ҵ�
			        if (currentNode == -1){
			            console.log("δ�ҵ�����λ��!")
				            return;
			
		}
		        let newNode = new Node(value);
		        newNode.next = currentNode.next;
		        currentNode.next = newNode;
		    }
	
		    //����ֵɾ�����
		    delete = (value) = >{
		        let currentNode = this.head;
		        let preNode = null;
		        while (currentNode != = null && currentNode.data != = value){
			            preNode = currentNode;
			            currentNode = currentNode.next;
			
		}
		        if (currentNode == null) return -1;
		        preNode.next = currentNode.next;
		    }
	
		     //�������н��
		    print = () = >{
		        let currentNode = this.head
			        //�����㲻Ϊ��
			        while (currentNode != = null){
			            console.log(currentNode.data)
				            currentNode = currentNode.next;
			
		}
		    }
	 }

//����
const list = new LinkList()
list.insert('xiao', 'head');
list.insert('lu', 'xiao');
list.insert('ni', 'head');
list.insert('hellow', 'head');
list.print()
console.log('-------------ɾ��Ԫ��------------')
list.delete('ni')
list.delete('xiao')
list.print()
console.log('-------------��ֵ����------------')
list.findByValue('lu')
console.log('-------------����������------------')
list.print()
