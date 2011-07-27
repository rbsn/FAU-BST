; $Date: 2009-09-22 15:20:27 +0200 (Tue, 22 Sep 2009) $, $Revision: 2221 $, $Author: benjamin $
; kate: encoding ISO-8859-15;
; vim: set fileencoding=latin-9:
; -*- mode: c; coding: latin-9 -*-

; STRUKTUREN

; TOC: nicht-fluechtige Register des Intel 80386 Prozessors

; Die folgenden Angaben belegen ebx_offset mit dem Wert 0, esi_offset mit 4
; edi_offset mit 8 usw. Dies entspricht den Abstaenden der Elemente ebx, esi,
; edi usw. der Struktur toc zum Anfang der Struktur (in Bytes).
; Die Reihenfolge der Registerbezeichnungen muss unbedingt mit der von
; struct toc uebereinstimmen.

[ABSOLUTE 0]
ebx_offset:	resd 1
esi_offset:	resd 1
edi_offset:	resd 1
ebp_offset:	resd 1
esp_offset:	resd 1
