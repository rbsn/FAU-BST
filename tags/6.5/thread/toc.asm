; $Date: 2009-09-22 15:20:27 +0200 (Tue, 22 Sep 2009) $, $Revision: 2221 $, $Author: benjamin $
; kate: encoding ISO-8859-15;
; vim: set fileencoding=latin-9:
; -*- mode: c; coding: latin-9 -*-

%include "thread/toc.inc"

; EXPORTIERTE FUNKTIONEN

[GLOBAL toc_switch]
[GLOBAL toc_go]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; TOC_GO : Startet den ersten Prozess ueberhaupt.
;
; C Prototyp: void toc_go (struct toc* regs);

toc_go:
	;Kickoffadr neuer Stackpointer
	mov eax, [esp+4]			;toc struct adr nach eax
	;mov ebx, [eax+ebx_offset]
	;mov esi, [eax+esi_offset]
	;mov edi, [eax+edi_offset]
	;mov ebp, [eax+ebp_offset]
	mov esp, [eax+esp_offset]
	pop ebp
	pop edi
	pop esi
	pop ebx
	ret

; TOC_SWITCH : Prozessumschaltung. Der aktuelle Registersatz wird     
;              gesichert und der Registersatz des neuen "thread of control"
;              wird in den Prozessor eingelesen.  
;
; C Prototyp: void toc_switch (struct toc* regs_now,
;                              struct toc* reg_then);

toc_switch:
; Hier muesst ihr selbst Code vervollstaendigen 
	mov ecx, [esp+4]			;now struct adr nach ecx
	mov eax, [esp+8]			;then struct
	
	;Ruecksichern
	;mov [ecx+ebx_offset], ebx
	;mov [ecx+esi_offset], esi
	;mov [ecx+edi_offset], edi
	;mov [ecx+ebp_offset], ebp
	;pusha
	push ebx 
	push esi
	push edi
	push ebp
	mov [ecx+esp_offset], esp

	;neu schreiben
	;mov ebx, [eax+ebx_offset]
	;mov esi, [eax+esi_offset]
	;mov edi, [eax+edi_offset]
	;mov ebp, [eax+ebp_offset]
	mov esp, [eax+esp_offset]
	pop ebp
	pop edi
	pop esi
	pop ebx
	;popa
	ret
