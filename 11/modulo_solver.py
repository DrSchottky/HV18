import gmpy2
 
c=0x7E65D68F84862CEA3FCC15B966767CCAED530B87FC4061517A1497A03D2
p=0xDD8E05FF296C792D2855DB6B5331AF9D112876B41D43F73CEF3AC7425F9
b=0x7BBE3A50F28B2BA511A860A0A32AD71D4B5B93A8AE295E83350E68B57E5
 
for i in range (1,100000): 
	inv = gmpy2.invert(b*i,p)
	a = c * inv % p
	a = hex(a).lstrip("0x")
	try:
		num = str(a).decode("hex")
		if "HV18" in num:
			print num, "(", i, ")"
	except:
		pass