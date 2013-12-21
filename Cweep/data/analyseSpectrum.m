filein = argv(){1}


m  = load( "-ascii", filein );
mz = m(:,4);
t  = m(:,1);

t(21)-t(20)
mz_fft = abs(fft(mz));
mz_fft = mz_fft(1:rows(mz)/2);
f      = (0:rows(mz)/2-1)/(rows(mz)*(t(21)-t(20)));

f1 = fopen('sweep.txt','a');
for i = 1:length(f)
    fprintf(f1,'%s\t%f\t%f\n', filein(6:7), f(i), mz_fft(i));
end
fprintf(f1, '\n\n');
fclose(f1);
