bool reverseList(Sqlist &L){
	char p;
	for(i=0;i<L.length/2;i++){
		p=L.elem[i];
		L.elem[i]=L.elem[L.length-i];
		L.elem[L.length-i]=p;
	}
	return OK;
}

bool reverseList_L(LNode &L){
	LNode p,q,s,*head,*end;
	p=L;
	q=p->next;
	s=q->next;
	head=&p;
	head->next=NULL;
	while(s->next){
		q->next=p;
		p=s;
		s=s->next;
		q=s;
		s=q->next;
	}
	return OK;
}

