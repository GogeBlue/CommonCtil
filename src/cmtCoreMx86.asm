;cmtCore assembly support
;i386 version for masm
.model flat
.code

;cx dx
;void cmtSpinLockEnter(cmtUint8* value, cmtUint64 MaxSpin)
@cmtSpinLockEnter@8 proc
	;ah=1
	xor ah, ah
	inc ah

	;���MaxSpin�Ƿ�Ϊ-1
	cmp edx, 0ffffffffh
	je cSLE_NoCount

	cSLE_SpinStart:
	;����ģʽ������ѭ������
	test edx, edx
	;��������������
	jz cSLE_EndMaxSpin
	dec edx
	
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
	cmpxchg byte ptr [ecx], ah
	;MaxSpin=0���������
	jz cSLE_EndNormal
	;MaxSpin!=0����������
	jmp cSLE_SpinStart

	cSLE_NoCount:
	xor al, al
	cmpxchg byte ptr [ecx], ah
	jnz cSLE_EndNormal

	cSLE_EndMaxSpin:
	xor eax, eax
	inc eax
	ret

	cSLE_EndNormal:
	xor eax, eax
	ret
@cmtSpinLockEnter@8 endp

end