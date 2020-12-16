#!/usr/bin/env Rscript

options(stringsAsFactors=F)
pdf.options(onefile=F, width=10, height=10)

args = commandArgs(T)
Rname = args[1]
rast = read.table(gzfile(Rname), row.names=1)

T = nrow(rast)
times = 1:T/1000

NN = ncol(rast)
spkmean = T/apply(rast, 2, sum)
spkcv = sapply(1:NN,
               function(n) {sp=which(rast[,n]>0); dl=c(sp, T)-c(0,sp)-spkmean[n];
                            sqrt(mean(dl^2))})

par(las=1, pch=20, mar=c(4,4,1,1), lwd=2, lty=1, cex=1.2)
image(times, 1:NN, as.matrix(rast), col=c(0,1), breaks=c(-1,1,2)/2,
      main=Rname)

if (length(args) > 1) {
    Tname = args[2]
    traj = read.delim(gzfile(Tname), row.names=1)

    ntypes = unique(sapply(strsplit(names(traj), '.', fixed=T), "[[", 1))
    ph = ceiling(sqrt(length(ntypes)))
    pw = ceiling(length(ntypes)/ph)
    par(mfrow=c(ph,pw), las=1, pch=20, mar=c(3.5,3.5,3,1), lwd=2, lty=1,
        mgp=c(2.5,1,0), cex.lab=1.3, cex=1.1)
    for (typ in ntypes) {
        plot(times, traj[,paste(typ, "v", sep='.')],
             t='l', ylim=c(-75,40), col=1,
             xlab='Time [s]', ylab='', main='')
        lines(times, traj[,paste(typ, "I", sep='.')], col=3, lwd=1)
        lines(times, traj[,paste(typ, "u", sep='.')], col=2)
        title(typ, adj=0, line=0.1)
    }
    legend("topleft", c("v","u","I"), lty=1, col=1:3, inset=c(.51,-.1), xpd=T, horiz=T, cex=.8)
}

if (length(args) > 2) {
    Pname = args[3]
    pars = read.delim(gzfile(Pname))
    types = c("RS", "IB", "CH", "FS", "LTS", "TC", "RZ")
    cols = sapply(pars[,1], function(x) which(types == x))
    par(mfrow=c(2,2), las=1, pch=20, mar=c(3.5,3.5,3,1), lwd=2, lty=1,
        mgp=c(2.5,1,0), cex.lab=1.3, cex=1.1)
    plot(pars[,"a"], pars[,"b"], xlim=c(0, .2), ylim=c(0.1, 0.3),
         col=cols, xlab='a', ylab='b')
    Ityp = which(types %in% unique(pars[,1]) )
    legend("topright", types[Ityp], lty=1, col=(1:length(types))[Ityp])
    plot(pars[,"c"], pars[,"d"], xlim=c(-75, -40), ylim=c(0,15),
         col=cols, xlab='c', ylab='d')
    plot(spkcv, 1000/spkmean, xlim=c(10, 150), ylim=c(5, 60), log='xy',
         col=cols, xlab='CV (ISI)', ylab='Firing rate [Hz]')
    xlims = range(1000/spkmean)
    brks = c(min(xlims[1]-1, 1), seq(3, 60, by=2), max(62, xlims[2]+1))
    h = hist(1000/spkmean[cols==Ityp[1]], br=brks, plot=F)
    plot(h$mids, h$dens, col=Ityp[1], t='s', lwd=3, 
         xlab='Firing rate [Hz]', ylab='Density', xlim=c(1, 60), main='')
    for (tt in Ityp[-1]) {
        h = hist(1000/spkmean[cols==tt], br=brks, plot=F)
        lines(h$mids, h$dens, col=tt, lwd=3, t='s')
    }
}

#! Rscript ../RasterPlots.R NeuronNetwork_spikes NeuronNetwork_sample_neurons NeuronNetwork_parameters