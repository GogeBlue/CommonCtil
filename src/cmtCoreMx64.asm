;cmtCore assembly support
;amd64 version for masm
.code

;cx dx r8 r9
;void cmtSpinLockEnter(cmtUint8* value, cmtUint64 MaxSpin)
cmtSpinLockEnter proc
	;ah=1
	xor ah, ah
	inc ah

	;���MaxSpin�Ƿ�Ϊ-1
	cmp rdx, 0ffffffffffffffffh
	je cSLE_NoCount

	cSLE_SpinStart:
	;����ģʽ������ѭ������
	test rdx, rdx
	;��������������
	jz cSLE_EndMaxSpin
	dec rdx
	
	xor al, al
	;cmpxchg��
	;if(op1==ax)
	;{
	;	op1=op2;
	;	rflags.zf=1;
	;}
	;else
	;{
	;	ax=op1;
	;	rflags.zf=0;
	;}
	lock cmpxchg byte ptr [rcx], ah
	;MaxSpin=0���������
	jz cSLE_EndNormal
	;MaxSpin!=0����������
	jmp cSLE_SpinStart

	cSLE_NoCount:
	xor al, al
	cmpxchg byte ptr [rcx], ah
	jz cSLE_EndNormal
	jmp cSLE_NoCount

	cSLE_EndMaxSpin:
	xor rax, rax
	inc rax
	ret

	cSLE_EndNormal:
	xor rax, rax
	ret
cmtSpinLockEnter endp

end