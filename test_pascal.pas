procedure sift(i,m:integer); {调整以i为根的子树 ,m为结点总数}
var k:integer;
begin
	a[0]:=a[i];	//if
	k:=2*i; {在完全二叉树中结点i的左孩子为2*i,右孩子为2*i+1}
	while k<=m do
	bgin
		if (k<m) and (a[k]<a[k+1]) then inc(k) {找出a[k]与a[k+1]中较大值 if }
		if a[0]<a[k] then
		begin
			a[i]:=a[k];
			i:=k;
			k:=2*i;
		end
		else
			k:=m+1;
	end ;
	a[i]:=a[0]; {将根放在合适的位置}
end;

procedure heapsort;
var  j:integer;
begin 
	for j:=n div 2 downto 1 do sift(j,n);
	for j:=n downto 2 do 
	begin 
		swap(a[1],a[j]);
		sift(1,j-1);
	end;
end;
